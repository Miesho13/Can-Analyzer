using CanAnalyzer.Store;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CanAnalyzer.ViewModel
{
  public class MainViewModel : ViewModelBase
  {
    private NavigationStore _navitagionStore;

    public ViewModelBase CurrentViewModel => _navitagionStore.CurrentViewModel;

    public MainViewModel(NavigationStore navitagionStore)
    {
      _navitagionStore = navitagionStore;

      _navitagionStore.CurrentViewModelChanged += OnCurrentViewModelChange;
    }

    private void OnCurrentViewModelChange()
    {
      OnPropertyChanged(nameof(CurrentViewModel));
    }
  }
}
