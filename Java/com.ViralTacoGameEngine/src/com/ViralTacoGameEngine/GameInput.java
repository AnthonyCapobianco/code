package com.ViralTacoGameEngine;

import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;
import java.awt.event.MouseWheelEvent;
import java.awt.event.MouseWheelListener;

public class GameInput implements KeyListener, MouseListener, MouseMotionListener, MouseWheelListener {

	private GameEngine ge;

	private final int NUM_KEYS = 256;
	private boolean[] keys = new boolean[NUM_KEYS];
	private boolean[] keysLast = new boolean[NUM_KEYS];

	private final int NUM_MOUSE = 5;
	private boolean[] mouseButton = new boolean[NUM_MOUSE];
	private boolean[] mouseButtonLast = new boolean[NUM_MOUSE];

	private int mousePositionX = 0;
	private int mousePositionY = 0;
	private int mouseWheelScroll = 0;

	public GameInput(GameEngine ge) {
		this.ge = ge;

		this.mousePositionX = 0;
		this.mousePositionY = 0;
		this.mouseWheelScroll = 0;

		ge.getWindow().getCanvas().addMouseListener(this);
		ge.getWindow().getCanvas().addMouseWheelListener(this);
		ge.getWindow().getCanvas().addMouseMotionListener(this);
		ge.getWindow().getCanvas().addKeyListener(this);
	}

	public void update() {
		this.mouseWheelScroll = 0;
		for (int i = 0; i < NUM_KEYS; i++) {
			this.keysLast[i] = keys[i];
		}
		for (int i = 0; i < NUM_MOUSE; i++) {
			this.mouseButtonLast[i] = this.mouseButton[i];
		}
	}

  // Key getters 
	public boolean isKey(int keyCode) {
		return this.keys[keyCode];
	}
	
	public boolean isKeyDown(int keyCode) {
		return (this.keys[keyCode] && !this.keysLast[keyCode]);
	}
	
	public boolean isKeyUp(int keyCode) {
		return (!this.keys[keyCode] && this.keysLast[keyCode]);
	}
	
	// Mouse button getters 
	public boolean isMouseButton(int mouseButtonCode) {
		return this.mouseButton[mouseButtonCode];
	}
	
	public boolean isMouseButtonDown(int mouseButtonCode) {
		return (this.mouseButton[mouseButtonCode] && !this.mouseButtonLast[mouseButtonCode]);
	}
	
	public boolean isMouseButtonUp(int mouseButtonCode) {
		return (!this.mouseButton[mouseButtonCode] && this.mouseButtonLast[mouseButtonCode]);		
	}


	@Override
	public void mouseWheelMoved(MouseWheelEvent e) {
		this.mouseWheelScroll = e.getWheelRotation();

	}

	@Override
	public void mouseDragged(MouseEvent e) {
		this.mousePositionX = (int) (e.getX() / ge.getScale());
		this.mousePositionY = (int) (e.getY() / ge.getScale());
	}

	@Override
	public void mouseMoved(MouseEvent e) {
		this.mousePositionX = (int) (e.getX() / ge.getScale());
		this.mousePositionY = (int) (e.getY() / ge.getScale());
	}

	@Override
	public void mouseClicked(MouseEvent e) {
		// TODO Auto-generated method stub

	}

	@Override
	public void mousePressed(MouseEvent e) {
		this.mouseButton[e.getButton()] = true;

	}

	@Override
	public void mouseReleased(MouseEvent e) {
		this.mouseButton[e.getButton()] = false;

	}

	@Override
	public void mouseEntered(MouseEvent e) {
		// TODO Auto-generated method stub

	}

	@Override
	public void mouseExited(MouseEvent e) {
		// TODO Auto-generated method stub

	}

	@Override
	public void keyTyped(KeyEvent e) {

	}

	@Override
	public void keyPressed(KeyEvent e) {
		this.keys[e.getKeyCode()] = true;
	}

	@Override
	public void keyReleased(KeyEvent e) {
		this.keys[e.getKeyCode()] = false;
	}

	// Getters
	public int getMousePositionX() {
		return mousePositionX;
	}

	public int getMousePositionY() {
		return mousePositionY;
	}

	public int getMouseWheelScroll() {
		return mouseWheelScroll;
	}

}
