package com.cruzdb;

import java.io.IOException;

/**
 *
 */
public class Log extends ZObject {

  static {
    Log.loadLibrary();
  }

  /**
   *
   */
  public static synchronized void loadLibrary() {
    String tmpDir = System.getenv("ZLOG_SHAREDLIB_DIR");
    try {
      NativeLibraryLoader.getInstance().loadLibrary(tmpDir);
    } catch (IOException e) {
      throw new RuntimeException("Unable to load the ZLog shared library: " + e);
    }
  }

  @Override
  protected void disposeInternal() {
    synchronized (this) {
      assert(isInitialized());
      disposeInternal(nativeHandle_);
    }
  }

  private Log() {
    super();
  }

  private native void disposeInternal(long handle);
}
