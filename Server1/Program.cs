using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace Server1
{
  internal class Program
  {
    // главный сокет сервера
    static Socket srvSocket = null;
    static void Main(string[] args)
    {
      Console.WriteLine("SERVER");
      // Создание экземпляра главного сокета сервера
      srvSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
      // настройка адреса и порта сервера для приема соединений от клиентов
      IPEndPoint srvIP = new IPEndPoint(IPAddress.Any, 12345);
      // связываение конечной точки с сокетом сервера
      srvSocket.Bind(srvIP);
      // включить прослушивание сокета сервера
      srvSocket.Listen(1000);
      Console.WriteLine("Server started on: {0}", srvIP.ToString());

      // ждать подключения клиента
      Socket client = srvSocket.Accept();
      // клиент подключился
      Console.WriteLine("Client conneted: {0} ==> {1}",
        client.LocalEndPoint.ToString(), client.RemoteEndPoint.ToString());

      // Посылка данных клиенту
      string msg = "Hello from Server!";
      client.Send(Encoding.UTF8.GetBytes(msg));

      // Получение данных от клиента
      byte[] buffer = new byte[1024];
      int size = client.Receive(buffer);
      Console.WriteLine("Recieve message from client: [{0}] {1}", size, Encoding.UTF8.GetString(buffer, 0, size));

      // закрытие клиентского сокета
      client.Close();

      // закрытие серверного сокета
      srvSocket.Close();

      Console.ReadLine();

    }
  }
}
