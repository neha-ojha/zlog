package com.cruzdb;

import java.io.IOException;

/**
 *
 */
public class NativeLibraryLoader {
  private static final NativeLibraryLoader instance = new NativeLibraryLoader();
  private static boolean initialized = false;

  private static final String sharedLibraryName = "zlogjni";

  private NativeLibraryLoader() {
  }

  public static NativeLibraryLoader getInstance() {
    return instance;
  }

  public synchronized void loadLibrary(final String tmpDir) throws IOException {
    System.loadLibrary(sharedLibraryName);
  }
}
