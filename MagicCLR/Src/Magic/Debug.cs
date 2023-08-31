namespace Magic
{
    public static unsafe partial class Debug
    {
        public static void Log(string msg){
            nativeLog(msg);
        }

        public static void Warn(string msg) {
            nativeWarn(msg);
        }

        public static void Error(string msg) {
            nativeError(msg);
        }

        public static void Critical(string msg) {
            nativeCritical(msg);
        }
    }
}
