using CanAnalyzer.Command;
using CanAnalyzer.Model;
using CanAnalyzer.Service;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Diagnostics;
using System.IO;
using System.IO.Ports;
using System.Linq;
using System.Xml.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace CanAnalyzer.ViewModel
{
  public class MainUserViewModel : ViewModelBase
  {
    private List<byte> bytes;

    private Analyzer _analyzer;
    private ComService _comService;

    private ObservableCollection<string> _comList;
    public ObservableCollection<string> ComList
    {
      get => _comList;
      set
      {
        _comList = value;
        OnPropertyChanged(nameof(ComList));
      }
    }

    private string _filterID;
    public string FilterID
    {
      get => _filterID;
      set
      {
        _filterID = value;
        OnPropertyChanged(nameof(FilterID));
      }
    }

    private string _filterMaskID;
    public string FilterMaskID
    {
      get => _filterMaskID;
      set
      {
        _filterMaskID = value;
        OnPropertyChanged(nameof(FilterMaskID));
      }
    }

    private int _selectBautRate;
    public int SelectBautRate
    {
      get => _selectBautRate;
      set
      {
        _selectBautRate = value;
        OnPropertyChanged(nameof(SelectBautRate));
      }
    }

    private string _selectCOM;
    public string SelectCOM
    {
      get => _selectCOM;
      set
      {
        bool isNoSet = false;
        if (_selectCOM == "<Set COM>")
        {
          isNoSet = true;
        }

        _selectCOM = value;

        if (isNoSet == true)
        {
          _comList.RemoveAt(0);
        }
        OnPropertyChanged(nameof(SelectCOM));
        InitReadCOM();
      }
    }

    private ObservableCollection<FrameViewModel> _frameViewModelCollection;
    public IEnumerable<FrameViewModel> FFrameViewModelCollection => _frameViewModelCollection;
    public IEnumerable<FrameViewModel> FrameViewModelCollection
    {
      get
      {
        if (FFrameViewModelCollection != null)
        {
          if (_finde == string.Empty)
          {
            return FFrameViewModelCollection;
          }
          else
          {
            return FFrameViewModelCollection.Where(u => u.CanAddres.Contains(Finde));
          }
        }
        else
        {
          return FFrameViewModelCollection;
        }

      }
    }

    private string _finde = string.Empty;
    public string Finde
    {
      get
      {
        return _finde;
      }
      set
      {
        _finde = value;
        OnPropertyChanged(nameof(Finde));
        OnPropertyChanged(nameof(FrameViewModelCollection));
      }
    }

    private FrameViewModel _select;
    public FrameViewModel Select
    {
      get => _select;
      set
      {
        _select = value;
        OnPropertyChanged(nameof(Select));
      }
    }

    private FrameViewModel _lastFrame;
    public FrameViewModel LastFrame
    {
      get => _lastFrame;
      set
      {
        _lastFrame = value;
        OnPropertyChanged(nameof(LastFrame));
      }
    }

    public ICommand Send { get; }

    public MainUserViewModel(Analyzer analyzer, ComService comservice)
    {
      _selectCOM = "<Set COM>";
      _analyzer = analyzer;
      
      _comService = comservice;

      bytes = new List<byte>();

      _frameViewModelCollection = new ObservableCollection<FrameViewModel>();

      _comList = new ObservableCollection<string>();

      if (string.IsNullOrEmpty(_comService.COM) == false)
      {
        _comService._serialPort.DataReceived += 
          new SerialDataReceivedEventHandler(DataReceivedHandler);
      }

      Send = new SendDataCommand(this, _comService);

      LoadPortCOM();
    }

    private void InitReadCOM()
    {
      
      _comService.OpenPort(SelectCOM);
      _comService._serialPort.ReadExisting();
      _comService._serialPort.DiscardInBuffer();
      _comService._serialPort.DiscardOutBuffer();
      _comService._serialPort.DataReceived +=
          new SerialDataReceivedEventHandler(DataReceivedHandler);
    }

    private void LoadPortCOM()
    {
      _comList.Add("<Set COM>");
      foreach (string port in SerialPort.GetPortNames())
      {
        _comList.Add(port);
      }
    }

    private void DataReceivedHandler(object sender, SerialDataReceivedEventArgs e)
    {
      SerialPort port = (SerialPort)sender;
      
      byte resiveByte = (byte)port.ReadByte();
      if (resiveByte != 0x0A)
      {
        bytes.Add(resiveByte);
      } 
      else
      {
        App.Current.Dispatcher.Invoke((Action)delegate
        {
          if (_frameViewModelCollection.Count > 100)
          {
            _frameViewModelCollection.RemoveAt(_frameViewModelCollection.Count - 1);
          }
          try
          {
            _frameViewModelCollection.Insert(
              0, new FrameViewModel(new Model.Frame(bytes.ToArray())));
            LastFrame = new FrameViewModel(new Model.Frame(bytes.ToArray()));

          }
          catch
          {

          }
          bytes.Clear();
        });
      }

    }
  }
}
