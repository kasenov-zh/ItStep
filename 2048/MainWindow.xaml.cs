using System;
using System.Collections.Generic;
using System.IO;
//using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Automation.Peers;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;


namespace _2048
{
  /// <summary>
  /// Interaction logic for MainWindow.xaml
  /// </summary>
  public partial class MainWindow : Window
  {
    public Window1 w1 = new Window1();

    public void EnumDir(string path)
    {
      

      System.IO.DirectoryInfo dir = new System.IO.DirectoryInfo(path);
      //var dirs = dir.EnumerateDirectories();
      IEnumerable<DirectoryInfo> dirs = dir.EnumerateDirectories();
      //var files = dir.EnumerateFiles();
      IEnumerable<FileInfo> files = dir.EnumerateFiles();
      //var files_info = dir.GetFiles();
      FileInfo[] files_info = dir.GetFiles();

      foreach (var item in dirs)
      {
        string name       = item.Name;
        string full_name  = item.FullName;
        FileInfo[] files_inf  = item.GetFiles();
        int files_cnt =  files_inf.Length;
        full_name = item.FullName;
      }
      foreach (var item in files)
      {
        string name       = item.Name;
        string full_name  = item.FullName;
        long   file_size  = item.Length;
        full_name = item.FullName;
      }
      foreach (var item in files_info)
      {
        string name = item.Name;
        string full_name = item.FullName;
        long file_size = item.Length;
        full_name = item.FullName;
      }

      w1.trDirs.Items.Clear();
      w1.trDirs.Items.Add(new TreeViewItem());
      (w1.trDirs.Items[0] as TreeViewItem).Header = path;
      (w1.trDirs.Items[0] as TreeViewItem).Items.Add("file1");
      (w1.trDirs.Items[0] as TreeViewItem).Items.Add("file2");
      (w1.trDirs.Items[0] as TreeViewItem).Items.Add("file3");
      //(w1.trDirs.Items[0] as TreeViewItem).ItemsSource = dir.GetDirectories();
      (w1.trDirs.Items[0] as TreeViewItem).ExpandSubtree();
      (w1.trDirs.Items[0] as TreeViewItem).IsSelected = true;

      w1.lvFiles.Items.Clear();
      //w1.lvFiles.ItemsSource = files_info;
      //w1.lvFiles.ItemsSource = dir.GetFiles();
      w1.lvFiles.Items.Add("sdcsdcsc");
      foreach(var f_item in dir.GetFiles())
      {

        GridView gv = w1.lvFiles.View as GridView;
        GridViewColumn gvc = gv.Columns[0];
        DataTemplate data = gvc.CellTemplate as DataTemplate;
        data.DataType = typeof(string);
        //data.DataCol1 = f_item.Name;
        DataTemplateKey dtk = data.DataTemplateKey as DataTemplateKey;

        //var sss = gvc.CellTemplate.DataType.ToString();
        //.DataTemplateKey = f_item.Name;



        w1.lvFiles.Items.Add(f_item.Name);
      }
    }

    public MainWindow()
    {
      //Thread.Sleep(2000);
      InitializeComponent();
      // Цвет плитки по умлочанию

      Brush brDefault = new SolidColorBrush(Colors.Coral);

      for (int i = 0; i < 4; i++)
      { // по строкам
        for (int j = 0; j < 4; j++)
        { // по столбцам
          Canvas cn = new Canvas();
          MainGrid.Children.Add(cn);
          // "Grid.Row" = "0"
          cn.SetValue(Grid.RowProperty, i);
          // "Grid.Col" = "0"
          cn.SetValue(Grid.ColumnProperty, j);
          cn.Tag = 0;
          cn.Background = brDefault;
          Thickness tk = new Thickness(10, 10, 10, 10);
          cn.Margin = tk;
          // cn.SetValue(MarginProperty, tk);
          // Присваивание имени элементу окна
          // Brik_1_2
          cn.Name = "Brik_" + i.ToString()
                      + "_" + j.ToString();
        }
      }
      MainGrid.ShowGridLines = false;

      string p = @"E:\Work\Source\VS2022\ItStep\2048\";
      EnumDir(p);

      w1.Show();
    }

    private void Window_ContentRendered(object sender,
                    EventArgs e)
    {
      int k = 0; // общий индекс по всем объектам MainGrid
      for (int i = 0; i < MainGrid.RowDefinitions.Count; i++)
      {
        for (int j = 0; j < MainGrid.ColumnDefinitions.Count; j++)
        {
          // k = i * MainGrid.ColumnDefinitions.Count + j;
          Canvas cn = MainGrid.Children[k] as Canvas;
          TextBox txt = new TextBox();
          txt.Text = cn.Name;
          cn.Children.Add(txt);

          Line line = new Line();
          line.Fill = Brushes.Black;
          line.Stroke = Brushes.Black;
          line.StrokeThickness = 4;

          line.X1 = 1;
          line.Y1 = 1;
          line.X2 = cn.ActualWidth;
          line.Y2 = cn.ActualHeight;
          cn.Children.Add(line);
          /*
          cn.OnRender

          DrawingVisual a = new DrawingVisual();
          a.Drawing

          Path path = new Path();
          path.C

          Pen shapeOutlinePen = new Pen(Brushes.Black, 2);
          shapeOutlinePen.Freeze();

          DrawingGroup dGroup = new DrawingGroup();
          using (DrawingContext dc = dGroup.Open())
          {
            dc.DrawRectangle(Brushes.Blue, shapeOutlinePen, new Rect(0, 0, 25, 25));

          }
          cn.Children

          DrawingContext cont = (new DrawingVisual()).RenderOpen();
          cont.DrawLine(
            new Pen(new SolidColorBrush(Colors.Brown), 2),
            new Point(1, 1), new Point(10, 10));
          cn.Children.Add(cont);

          //DrawingVisual dw = new DrawingVisual();
          //DrawingContext cont = dw.RenderOpen();
          //cont.DrawEllipse();
          //cn.Children.Add(txt);
          */
          k++;
        }

      }
    }
  }
}
