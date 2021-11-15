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
            TcpListener myList = new TcpListener(ipAd, port);

            /* Start Listeneting at the specified port */
            myList.Start();

            Console.WriteLine("The server is running at port 8001...");
            Console.WriteLine("The local End point is  :" + myList.LocalEndpoint);
            Console.WriteLine("Waiting for a connection.....");

            Socket s = myList.AcceptSocket();
            Console.WriteLine("Connection accepted from " + s.RemoteEndPoint);

            byte[] b = new byte[100];
            int k = s.Receive(b);
            Console.WriteLine("Recieved...");
            for (int i = 0; i < k; i++)
                Console.Write(Convert.ToChar(b[i]));

            //Send response
            ASCIIEncoding asen = new ASCIIEncoding();
            s.Send(asen.GetBytes("AOK."));
            Console.WriteLine("\nSent Acknowledgement AOK");
            /* clean up */
            s.Close();
            myList.Stop();

        }
        catch (Exception e)
        {
            Console.WriteLine("Error..... " + e.StackTrace);
        }
    }

}
