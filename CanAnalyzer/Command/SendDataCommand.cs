using CanAnalyzer.Model;
using CanAnalyzer.Service;
using CanAnalyzer.ViewModel;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CanAnalyzer.Command
{
  public class SendDataCommand : CommandBase
  {
    private MainUserViewModel _mainUserviewmodel;
    private ComService _comservice;

    public SendDataCommand(MainUserViewModel mainUserviewmodel, ComService comservice)
    {
      _mainUserviewmodel = mainUserviewmodel;
      _comservice = comservice;
    }

    public override void Execute(object parameter)
    {
      SetDataForSend send = new SetDataForSend(
        Convert.ToInt32(_mainUserviewmodel.FilterID),
        Convert.ToInt32(_mainUserviewmodel.FilterMaskID),
        _mainUserviewmodel.SelectBautRate);

      _comservice._serialPort.Write(send.Send(), 0, send.Send().Length);
    }


  }
}
