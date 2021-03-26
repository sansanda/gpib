
import java.io.IOException;
import java.nio.file.FileSystems;
import java.util.Enumeration;
import be.ac.ulb.gpib.*;
import be.ac.ulb.tools.*;

/**
 * Clase de prueba para testear el buen funcionamiento de la libreria JPIB v1.2 para el control de los instrumentos GPIB usando Java.
 * Antes de hacer funcionar el test asegurate que has seleccionado la libreria JPIB.jar correspondiente a la vesion JPIB_v1.2
 * @author DavidS
 * @source https://github.com/sebastiangoetz/jouleunit/blob/master/profilers/org.qualitune.jouleunit.wt210/src/org/qualitune/jouleunit/wt210/WT210Util.java	
 * @javadoc http://jpib.sourceforge.net/javadoc/V1_2_0/index.html
 * 
 */
public class Test_JPIB_v1_2 {

	/** Indicates whether or not the native driver has been loaded, yet. */
	private static boolean libraryLoaded = false;
	
	private static boolean loadLibrary() throws IllegalStateException {

		if (!libraryLoaded) {
			/* Load the OS depended Class-Driver */
			
			String absolutePath;
			
			switch (OSUtils.getOS()) {
			
				case WINDOWS32:
					absolutePath = FileSystems.getDefault().getPath("..\\..\\..","\\java_development_libraries\\comms\\parallel\\GPIB\\JPIB V1.2\\jpib_32.dll").normalize().toAbsolutePath().toString();
					break;
					
				case WINDOWS64:
					absolutePath = FileSystems.getDefault().getPath("..\\..\\..","\\java_development_libraries\\comms\\parallel\\GPIB\\JPIB V1.2\\jpib_64.dll").normalize().toAbsolutePath().toString();
					break;
	
				default: throw new IllegalStateException("No supported driver for OS "+ OSUtils.getOS());
			}

			System.load(absolutePath);
			
			libraryLoaded = true;
		}

		return true;
	}
	
	
    public static void main(String[] args) {
    	
        GPIBDeviceIdentifier deviceIdentifier;
        Enumeration<?> gpibDevicesList;
        GPIBDevice myDevice;
		
        	Test_JPIB_v1_2.loadLibrary();
	        
			try {
				
				
				GPIBDeviceIdentifier.initialize("be.ac.ulb.gpib.WindowsGPIBDriver", false);
				
				//System.out.println(GPIBDeviceIdentifier.driverLoaded());
				
				gpibDevicesList = GPIBDeviceIdentifier.getDevices();
				
				System.out.println("Libary path: " +  System.getProperty("java.library.path"));
				
				if (!gpibDevicesList.hasMoreElements()) 
				{
					System.out.println("No instruments detected on the BUS GPIB");
					return;
				}
				
				while (gpibDevicesList.hasMoreElements())
			    {
					deviceIdentifier = (GPIBDeviceIdentifier) gpibDevicesList.nextElement();
					
					myDevice = new GPIBDevice(deviceIdentifier.getAddress(), deviceIdentifier.getDriver());
					
					myDevice.open(1000.0f);
					
					//System.out.println("----" + myDevice.sendCommand("*IDN?") + "----");
					
					myDevice.writeCommand("SYST:BEEP OFF");
					myDevice.writeCommand("DISPLAY:ENABLE ON");
					myDevice.writeCommand("DISPLAY:WINDOW1:TEXT:STATE ON");
					myDevice.writeCommand("DISPLAY:WINDOW1:TEXT:DATA 'HOLA MUNDOs'");
					
					System.out.println(myDevice.sendCommand("DISPLAY:WINDOW1:TEXT:DATA?"));
					//System.out.println(myDevice.sendCommand("*STB?"));
					
			    }
				
				
			} catch (Exception e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			

			
        
    }
}