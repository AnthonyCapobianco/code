package com.ViralTacoGameEngine.source;

import javax.swing.JFrame;
import java.awt.image.BufferedImage;
import java.awt.image.BufferStrategy;
import java.awt.Canvas;
import java.awt.Graphics;
import java.awt.Dimension;
import java.awt.BorderLayout;

public class Window {
  private JFrame frame;
  private BufferedImage image;
  private Canvas canvas;
  private BufferStrategy bs;
  private Graphics g;
  
  private static final int NUMBER_OF_BUFFERS = 2;
  
  public Window(GameEngine ge) {
    image = new BufferedImage(ge.getWidth(), ge.getHeight()
                             , BufferedImage.TYPE_INT_RGB
    );
    Dimension s = new Dimension((int) (ge.getWidth() * ge.getScale())
                              , (int) (ge.getHeight() * ge.getScale())
    );
    
    canvas = new Canvas();
    canvas.setPreferredSize(s);
    canvas.setMaximumSize(s);
    canvas.setMinimumSize(s);
    canvas.setFocusable(true)﻿; // Let the canvas be focused on for the mouse events
    
    frame = new JFrame(ge.getTitle());
    frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    frame.setLayout(new BorderLayout());
    frame.add(canvas, BorderLayout.CENTER);
    frame.pack(); // Make frame size of canvas
    frame.setLocationRelativeTo(null); // Middle of the screen
    frame.setResizable(false); // Not resizable 
    frame.setVisible(true); // Make it visible otherwise we just wasted a lot of time
    
    canvas.createBufferStrategy(NUMBER_OF_BUFFERS);
    bs = canvas.getBufferStrategy();
    g = bs.getDrawGraphics(); 
  }
  
  public void update() {
    g.drawImage(image, 0, 0, canvas.getWidth(), canvas.getHeight(), null);
    bs.show();
  }
  
  // Getters
  public BufferedImage getImage() { return this.image; }
  public Canvas getCanvas() { return this.canvas; }
}