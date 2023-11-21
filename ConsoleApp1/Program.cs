using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;

/*Задание 1
Создайте оконное приложение, генерирующее набор простых чисел в диапазоне, указанном пользователем.
Если не указана нижняя граница, поток с стартует с 2.
Если не указана верхняя граница, генерирование происходит до завершения приложения.
Используйте механизм потоков. Числа должны отображаться в оконном интерфейсе.

Задание 2
Добавьте к первому заданию поток, генерирующий набор чисел Фибоначчи.
Числа должны отображаться в оконном интерфейсе.
*/

namespace ConsoleApp3
{
  class Program
  {

    static void Main(string[] args)
    {


      ThreadPool.SetMinThreads(2, 2);
      ThreadPool.SetMaxThreads(int.MaxValue, int.MaxValue);
      Thread Th = new Thread(Pruf);
      Th.Start();
      Th.Join();
      Thread Th2 = new Thread(Fib);
      Th2.Start();
      Th2.Join();
      //for (int i = 0; i < 5; i++)
      //{
      //    Console.WriteLine("Main thread: {0}",i);
      //    Thread.Sleep(100);
      //}



    }
    static void Pruf()
    {
      int Start = int.Parse(Console.ReadLine());
      int Finish = int.Parse(Console.ReadLine());

      for (Start = 0; Start < Finish; Start++)
      {
        Console.WriteLine("Ваши числа: " + Start);

      }
    }
    static void Fib()
    {
      Console.Write("Введите начальное значение: ");
      int start = int.Parse(Console.ReadLine());

      Console.Write("Введите конечное значение: ");
      int end = int.Parse(Console.ReadLine());
      int a = 0, b = 1, c = 0;

      while (c <= end)
      {
        if (c >= start)
        {
          Console.WriteLine(c);
        }

        a = b;
        b = c;
        c = a + b;
      }
    }
  }
}
