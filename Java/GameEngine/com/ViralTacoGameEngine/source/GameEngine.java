package com.ViralTacoGameEngine.source;

public class GameEngine implements Runnable {
  private static final boolean SHOW_FPS = true; 
  
  private Thread engineThread;
  private Window gameWindow;
  private Renderer gameRenderer;
  
  private boolean isRunning = false;
  private final double UPDATE_RATE_CAP = 1.0/60.0;
  
  // Display variables 
  private int width = 480;
  private int height = 300;
  private float scale = 3.0f;
  private String title = "Window title";
  
  public GameEngine() {
    // this.start();
  }
  
  public void start() {
    gameWindow = new Window(this);
    gameRenderer = new Renderer(this);
    
    engineThread = new Thread(this);
    engineThread.run(); // Calls run() method 
  }
  
  public void run() {
    isRunning = true;
    
    // Time variable
    double firstTime = 0.0;
    double lastTime = System.nanoTime() / 1.0E9; // System.nanoTime() / 1 billion
    double passedTime = 0.0;
    double unprocessedTime = 0.0;
    
    double frameTime = 0.0;
    int frames = 0;
    int fps = 0;
    
    boolean doRender = false;
    
    
    while (isRunning) {
      doRender = false;
      
      firstTime = System.nanoTime() / 1.0E9;
      passedTime = firstTime - lastTime;
      lastTime = firstTime;
      
      unprocessedTime += passedTime;
      frameTime += passedTime;
      
      while (unprocessedTime >= UPDATE_RATE_CAP) {
        unprocessedTime -= UPDATE_RATE_CAP;
        doRender = true;
        
        // TODO: Update game
        
        if (SHOW_FPS) {
          if (frameTime >= 1.0) {
            frameTime = 0.0;
            fps = frames;
            frames = 0;
          }
          System.err.format("Game tick; FPS: %d\n", fps);
        }
      }
      
      if (doRender) {
        gameRenderer.clear();
        gameWindow.update();
        frames++;
        
      } else {
        try {
          Thread.sleep(1); // Sleep for 1ms
        } catch (InterruptedException e) {
          e.printStackTrace();
        }
      } // if (doRender)
    } // while (isRunning)
    
    collectGarbage(); // Just collect garbage, we're done running. 
  }
  
  public void stop() {
    
  }
  
  private void collectGarbage() {
    
  }
  
  public static void main(String[] args) {
    GameEngine ge = new GameEngine();
    ge.start();
  }
  
  // Getters
  public int getWidth() { return this.width; }
  public int getHeight() { return this.height; }
  public float getScale() { return this.scale; }
  public String getTitle() { return this.title; }
  public Window getWindow() { return this.gameWindow; }
  
  // Setters
  public void setWidth(int width) { this.width = width; }
  public void setHeight(int height) { this.height = height; }
  public void setScale(float scale) { this.scale = scale; }
  public void setTitle(String title) { this.title = title; }
  
}