package com.ViralTacoGameEngine;

import java.awt.image.DataBufferInt;

public class GameRenderer {
	private static final int BLACK = 0xff000000;
	private int pixelWidth = 0;
	private int pixelHeight = 0;

	private int[] pixels;

	public GameRenderer(GameEngine ge) {
		pixelWidth = ge.getWidth();
		pixelHeight = ge.getHeight();
		pixels = ((DataBufferInt) ge.getWindow().getImage().getRaster().getDataBuffer()).getData();
	}

	public void clear() {
		for (int i = 0; i < this.pixels.length; i++) {
			this.pixels[i] = 0;
		}
	}
}