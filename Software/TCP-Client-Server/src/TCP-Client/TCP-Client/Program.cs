// See https://aka.ms/new-console-template for more information
using System;
using System.IO;
using System.Net;
using System.Text;
using System.Net.Sockets;


public class clnt
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
            Console.WriteLine("Provide an address and port");
            return;
        }


        try
        {
            TcpClient tcpclnt = new TcpClient();
            Console.WriteLine("Connecting.....");

            string ip = args[0];
            Int32 port= Int32.Parse(args[1]);

            tcpclnt.Connect(ip, port);
            // use the ipaddress as in the server program

            Console.WriteLine("Connected");
            Console.Write("Enter the string to be transmitted : ");

            String str = Console.ReadLine();
            Stream stm = tcpclnt.GetStream();

            ASCIIEncoding asen = new ASCIIEncoding();
            byte[] ba = asen.GetBytes(str);
            Console.WriteLine("Transmitting.....");

            stm.Write(ba, 0, ba.Length);

            byte[] bb = new byte[100];
            int k = stm.Read(bb, 0, 100);

            for (int i = 0; i < k; i++)
                Console.Write(Convert.ToChar(bb[i]));

            tcpclnt.Close();
        }

        catch (Exception e)
        {
            Console.WriteLine("Error..... " + e.StackTrace);
        }
    }

}