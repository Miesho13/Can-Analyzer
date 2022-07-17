using CanAnalyzer.Model;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CanAnalyzer.Service
{
  public class ComService
  {
    public SerialPort _serialPort;

    public string COM { get; set; }

    public ComService()
    {
      COM = string.Empty;
      _serialPort = new SerialPort();
      _serialPort.Encoding = System.Text.Encoding.GetEncoding(28591);
    }

    public void OpenPort(string com)
    {
      COM = com;
      _serialPort.Close();
      _serialPort.PortName = COM;
      _serialPort.BaudRate = 9600;
      _serialPort.Parity = Parity.None;
      _serialPort.StopBits = StopBits.One;
      _serialPort.DataBits = 8;
      _serialPort.Handshake = Handshake.None;
      _serialPort.Open();

    }
  }
}
