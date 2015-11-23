static int B = 0;
static int H = 0;
static boolean flag = true;

static {
    flag = true;
    Scanner sc = new Scanner(System.in);
    B = sc.nextInt();
    if(B <= 0) {
        System.out.println("java.lang.Exception: Breadth and height must be positive");
        flag = false;
    } else {
        H = sc.nextInt();
        if(H <= 0) {
            System.out.println("java.lang.Exception: Breadth and height must be positive");
            flag = false;
        }
    }
}
