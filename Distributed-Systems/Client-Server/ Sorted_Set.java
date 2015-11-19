import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.File;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.NavigableMap;
import java.util.Set;
import java.util.TreeMap;
import java.util.TreeSet;
import java.util.concurrent.Callable;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ConcurrentMap;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

import org.newsclub.net.unix.AFUNIXServerSocket;
import org.newsclub.net.unix.AFUNIXSocketAddress;

public class Solution implements Runnable {
    private enum Method {
        ADD_SCORE(1) {
            @Override
            public int[] call(DataStore store, int... args) {
                store.addScore(args[0], args[1]);
                return new int[0];
            }
        },

        REMOVE_KEY(2) {
            @Override
            public int[] call(DataStore store, int... args) {
                store.removeKey(args[0]);
                return new int[0];
            }
        },

        GET_SIZE(3) {
            @Override
            public int[] call(DataStore store, int... args) {
                return new int[] {store.getSize()};
            }
        },

        GET_KEY_VALUE(4) {
            @Override
            public int[] call(DataStore store, int... args) {
                return new int[] {store.getKeyValue(args[0])};
            }
        },

        GET_RANGE(5) {
            @Override
            public int[] call(DataStore store, int... args) {
                return mapToArray(store.getRange(args[0], args[1]));
            }
        };

        private final int cmd;

        Method(int cmd) {
            this.cmd = cmd;
        }

        public abstract int[] call(DataStore store, int... args);

        public static Method valueOf(int cmd) {
            for (Method method : values()) {
                if (cmd == method.cmd)
                    return method;
            }
            return null;
        }
    }

    private enum Reducer {
        GET_RANGE(5) {
            @Override
            public int[] reduce(Collection<int[]> results) {
                Map<Integer, Set<Integer>> map = new TreeMap<>();
                for (int[] result : results) {
                    for (int i = 0; i < result.length; i += 2) {
                        Set<Integer> set = map.get(result[i]);
                        if (set == null)
                            map.put(result[i], set = new TreeSet<>());
                        set.add(result[i + 1]);
                    }
                }
                return mapToArray(map);
            }
        };

        private final int cmd;

        Reducer(int cmd) {
            this.cmd = cmd;
        }

        public abstract int[] reduce(Collection<int[]> results);

        public static Reducer valueOf(int cmd) {
            for (Reducer reducer : values()) {
                if (cmd == reducer.cmd)
                    return reducer;
            }
            return null;
        }
    }

    private static class DataStore {
        private final Map<Integer, Integer> fwd = new HashMap<>();
        private final NavigableMap<Integer, Set<Integer>> rev = new TreeMap<>();

        private void refreshScore(int key, Integer score, Integer old) {
            if (old != null)
                rev.get(old).remove(key);
            if (score != null) {
                Set<Integer> keys = rev.get(score);
                if (keys == null)
                    rev.put(score, keys = new HashSet<>());
                keys.add(key);
            }
        }

        public synchronized void addScore(int key, int score) {
            refreshScore(key, score, fwd.put(key, score));
        }

        public synchronized void removeKey(int key) {
            refreshScore(key, null, fwd.remove(key));
        }

        public synchronized int getSize() {
            return fwd.size();
        }

        public synchronized int getKeyValue(int key) {
            Integer value = fwd.get(key);
            return value != null ? value : 0;
        }

        public synchronized NavigableMap<Integer, Integer> getRange(int lower, int upper) {
            NavigableMap<Integer, Integer> result = new TreeMap<>();
            for (Map.Entry<Integer, Set<Integer>> entry
                    : rev.subMap(lower, true, upper, true).entrySet()) {
                for (Integer key : entry.getValue())
                    result.put(key, entry.getKey());
            }
            return result;
        }
    }

    private static final ConcurrentMap<Integer, DataStore> DATA_STORES = new ConcurrentHashMap<>();

    private final Socket s;

    public Solution(Socket s) {
        this.s = s;
    }

    @Override
    public void run() {
        try (DataInputStream in = new DataInputStream(s.getInputStream());
             DataOutputStream out = new DataOutputStream(s.getOutputStream())) {
            while (true) {
                int size = in.readInt();
                int[] request = new int[size];
                for (int i = 0; i < size; ++i)
                    request[i] = in.readInt();

                int[] response = dispatch(request);
                if (response == null)
                    return;

                out.writeInt(response.length);
                for (int value : response)
                    out.writeInt(value);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static DataStore getDataStore(int set) {
        DataStore result = DATA_STORES.get(set);
        if (result != null)
            return result;
        synchronized (DATA_STORES) {
            result = DATA_STORES.get(set);
            if (result == null)
                DATA_STORES.put(set, result = new DataStore());
            return result;
        }
    }

    private static int[] mapToArray(Map<Integer, ?> map) {
        int[] result = new int[map.size() * 2];
        int i = -1;
        for (Map.Entry<Integer, ?> entry : map.entrySet()) {
            int key = entry.getKey();
            Object value = entry.getValue();
            if (value instanceof Integer) {
                result[++i] = key;
                result[++i] = (Integer) value;
            } else if (value instanceof Collection) {
                for (Object item : (Collection<?>) value) {
                    result[++i] = key;
                    result[++i] = (Integer) item;
                }
            }
        }
        return result;
    }

    private static int[] singleDispatch(Method method, int set, int[] args) {
        return method.call(getDataStore(set), args);
    }

    private static int[] multiDispatch(final Method method, Reducer reducer,
                                       int[] sets, final int[] args) {
        List<Callable<int[]>> callables = new ArrayList<>();
        for (int set : sets) {
            final DataStore store = getDataStore(set);
            callables.add(new Callable<int[]>() {
                @Override
                public int[] call() {
                    return method.call(store, args);
                }
            });
        }

        ExecutorService executor = Executors.newCachedThreadPool();
        List<int[]> results = new ArrayList<>();
        try {
            for (Future<int[]> future : executor.invokeAll(callables))
                results.add(future.get());
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
            return null;
        } catch (ExecutionException e) {
            e.getCause().printStackTrace();
            return null;
        } finally {
            executor.shutdown();
        }

        return reducer.reduce(results);
    }

    private static int[] dispatch(int[] request) {
        int cmd = request[0];
        Method method = Method.valueOf(cmd);
        if (method == null)
            return null;
        Reducer reducer = Reducer.valueOf(cmd);
        if (reducer == null)
            return singleDispatch(method, request[1], Arrays.copyOfRange(request, 2, request.length));

        int i = 0;
        while (++i < request.length) {
            if (request[i] == 0)
                break;
        }
        return multiDispatch(method, reducer, Arrays.copyOfRange(request, 1, i),
                Arrays.copyOfRange(request, i + 1, request.length));
    }

    public static void main(String[] args) throws IOException {
        ServerSocket ss = AFUNIXServerSocket.bindOn(new AFUNIXSocketAddress(new File("socket")));
        while (true)
            new Thread(new Solution(ss.accept())).start();
    }
}
