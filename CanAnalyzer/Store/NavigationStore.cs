using CanAnalyzer.ViewModel;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CanAnalyzer.Store
{
  public class NavigationStore
  {
    private ViewModelBase _currentVeiwModel;
    public ViewModelBase CurrentViewModel
    {
      get => _currentVeiwModel;
      set
      {
        _currentVeiwModel = value;
        OnCurrentViewModelChange();
      }
    }

    private void OnCurrentViewModelChange()
    {
      CurrentViewModelChanged?.Invoke();
    }

    public event Action CurrentViewModelChanged;

  }
}
