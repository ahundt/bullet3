
#include <string.h>
#include "ActiveSocket.h"       // Include header for active socket object definition

int main(int argc, char **argv)
{
    CActiveSocket socket;       // Instantiate active socket object (defaults to TCP).
    char          time[50];

    memset(&time, 0, 50);

    //--------------------------------------------------------------------------
    // Initialize our socket object 
    //--------------------------------------------------------------------------
    socket.Initialize();

    //--------------------------------------------------------------------------
    // Create a connection to the time server so that data can be sent
    // and received.
    //--------------------------------------------------------------------------
//    if (socket.Open("time-C.timefreq.bldrdoc.gov", 13))
      if (socket.Open("localhost", 6667))
  {
        //----------------------------------------------------------------------
        // Send a requtest the server requesting the current time.
        //----------------------------------------------------------------------
		char data[1024];
		sprintf(data,"%s","Hello!");
		int len = strlen(data);
		data[len]=0;
		len++;
        if (socket.Send((const uint8 *)data, len))
        {
            //----------------------------------------------------------------------
            // Receive response from the server.
            //----------------------------------------------------------------------
            int rec = socket.Receive(len);
			if (rec)
			{
						uint8* data = socket.GetData();
				memcpy(&time, data, len);
				printf("%s\n", time);
			}

            //----------------------------------------------------------------------
            // Close the connection.
            //----------------------------------------------------------------------
            socket.Close();
        }
    }


    return 1;
}
