using CanAnalyzer.Model;
using CanAnalyzer.Service;
using CanAnalyzer.Store;
using CanAnalyzer.ViewModel;
using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Threading.Tasks;
using System.Windows;
using System.Diagnostics;

namespace CanAnalyzer
{
  /// <summary>
  /// Interaction logic for App.xaml
  /// </summary>
  public partial class App : Application
  {
    private Analyzer _analyzer;
    private readonly ComService _comservice;
    private readonly NavigationStore _navigationStore;

    public App()
    {
      _analyzer = new Analyzer();
      _comservice = new ComService();
      _navigationStore = new NavigationStore();
    }

    protected override void OnStartup(StartupEventArgs e)
    {
      _navigationStore.CurrentViewModel = new MainUserViewModel(_analyzer, _comservice);

      MainWindow = new MainWindow()
      {
        DataContext = new MainViewModel(_navigationStore)
      };
      MainWindow.Show();

      base.OnStartup(e);
    }
    
  }
}
