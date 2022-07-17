using CanAnalyzer.Model;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CanAnalyzer.ViewModel
{
  public class FrameViewModel : ViewModelBase
  {
    private readonly Frame _frame;

    public String CanAddres => $"0x{_frame.CanAddres}";

    public String RTR => $"0x{_frame.RTR}";

    public String IDE => $"0x{_frame.IDE}";

    public String DLC => $"0x{_frame.DLC}";

    public String DataHex => _frame.Data;

    public String DataAsci => $"0x{_frame.DataHex}";

    public String ContentHex => _frame.ToString("HEX");

    public String ContentAscii => _frame.ToString("ASCII");

    public String ReceiveTime => DateTime.Now.ToString("HH:mm:ss");

    public FrameViewModel(Frame frame)
    {
      _frame = frame;
    }

  }
}