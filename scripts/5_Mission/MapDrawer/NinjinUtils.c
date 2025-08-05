class NinjinUtils {
    static int screenWidth, screenHeight;
    static float widthScale, heightScale;
    static void UpdateScreenSize()
    {
        GetScreenSize(screenWidth, screenHeight);
        widthScale = screenWidth / 1920.0;
        heightScale = screenHeight / 1080.0;
    }
}
