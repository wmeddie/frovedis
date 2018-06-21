package com.nec.frovedis.Jexrpc;

//--- singleton class ---
public class FrovedisServer implements java.io.Serializable {
  public Node master_node;
  public int worker_size;
  private static boolean instantiated = false;
  private static String command = "mpirun -np 2 ./frovedis_server"; //default command
  private static FrovedisServer server;

  private FrovedisServer() {
    master_node = JNISupport.getMasterInfo(command); // native call
    worker_size = JNISupport.getWorkerSize(master_node); // native call
    instantiated = true;
    //System.out.println("\nServer instance created with command: " + command);
    //System.out.println(toString());
  }
  private static FrovedisServer createOrGetServer() {
    if (!instantiated) server = new FrovedisServer();
    return server;
  }
  // if called, before calling initialize,
  // it will try to create the server instance with default command and return
  // if server is already initialized, it simply returns the same server
  public static FrovedisServer getServerInstance() {
      return createOrGetServer();
  }
  // Spark programmar can call this method in the very begining,
  // if they want to initialize the Frovedis server with
  // different command other than the default one.
  public static FrovedisServer initialize(String cmd) {
      if(!instantiated) command = cmd;
      else System.out.println("Frovedis server is already initialized!!");
      return createOrGetServer();
  }
  public static void shut_down() {
    if(instantiated) { 
      JNISupport.cleanUPFrovedisServer(getServerInstance().master_node); // native call
      JNISupport.finalizeFrovedisServer(getServerInstance().master_node); // native call
      instantiated = false;
    }
  }
  public static void display() {
    if(instantiated) System.out.println(getServerInstance().toString());
    else System.out.println("No server to display!\n");
  }
  @Override
  public String toString() { 
    if(instantiated) 
      return "Master Node (" + master_node.get_host() + "," + 
              master_node.get_port() + ") has " + worker_size + " workers.\n";
    else return "Server not found";
  }
	/*
  @Override
  protected void finalize() {
    shut_down();
  }
	*/
}
