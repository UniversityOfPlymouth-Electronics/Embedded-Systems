using System;
using System.Text;
using System.Net;
using System.Net.Sockets;

public class serv
{
    public static void Main(string[] args)
    {
        if (args == null)
        {
            Console.WriteLine("Please provide your local IP address as a single parameter");
            return;
        }

        if (args.Length != 2)
        {
            Console.WriteLine("Specify an IP address (127.0.0.1 for local loopback) and port (e.g. 8001)");
            return;
        } 

        try
        {
            IPAddress ipAd = IPAddress.Parse(args[0]);

            Int32 port = Int32.Parse(args[1]);

            // use local m/c IP address, and 
            // use the same in the client

            /* Initializes the Listener */
            TcpListener myListener = new TcpListener(ipAd, port);

            /* Start Listeneting at the specified port */
            myListener.Start();

            Console.WriteLine($"The server is running at port {port}");
            Console.WriteLine("The local End point is  :" + myListener.LocalEndpoint);
            Console.WriteLine("Waiting for a connection.....");

            bool keepGoing = true;

            do
            {
                //Block on incoming connection
                Socket s = myListener.AcceptSocket();
                Console.WriteLine("Connection accepted from " + s.RemoteEndPoint);

                //Read incoming TCP data
                byte[] b = new byte[100];
                int k = s.Receive(b);

                //Check for "END"
                if ((b[0] == 'E') && (b[1] == 'N') && (b[2] == 'D'))
                {
                    keepGoing = false;
                } else
                {
                    //Echo received data to the console
                    Console.WriteLine("Received...");
                    for (int i = 0; i < k; i++)
                        Console.Write(Convert.ToChar(b[i]));
                }

                //Send response back to client (as raw bytes)
                ASCIIEncoding asen = new ASCIIEncoding();
                s.Send(asen.GetBytes("AOK."));
                Console.WriteLine("\nSent Acknowledgement AOK");

                //clean up
                s.Close();

            } while (keepGoing);

            myListener.Stop();

        }
        catch (Exception e)
        {
            Console.WriteLine("Error..... " + e.StackTrace);
        }
    }

}
