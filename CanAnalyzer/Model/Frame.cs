using CanAnalyzer.Exceptions;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CanAnalyzer.Model
{
  public class Frame
  {
    private Byte[] _reciveData;

    public String CanAddres { get; }

    public String RTR { get; }

    public String IDE { get; }

    public String DLC { get; }

    public String Data { get; }

    public String DataHex { get; }

    public String DataDec { get; }

    public Frame(Byte[] reciveData)
    {
      _reciveData = reciveData;

      CanAddres = parsCanAddres();

      RTR = parsRTR();

      IDE = ParsIDE();

      DLC = ParsDLC();

      Data = ParsData();

      DataHex = ParsDataHex();

      if (Convert.ToInt32(DLC, 16) != _reciveData.Length - 2)
      {
        throw new InvalidFrameException("Incorect frame");
      }

    }

    private string ParsDataHex()
    {
      string retString = string.Empty;
      foreach (var data in Data)
      {
        retString += $"0x{Convert.ToInt32(data).ToString("X")} ";
      }

      return retString;
    }

    public override bool Equals(object? obj)
    {
      return obj is Frame frame &&
             _reciveData == frame._reciveData;
    }

    public override int GetHashCode()
    {
      return HashCode.Combine(_reciveData);
    }

    public string ToString(String varaint = "A")
    {
      if (varaint == "HEX")
      {
        string retString = string.Empty;
        foreach (var data in _reciveData)
        {
          retString += Convert.ToInt32(data).ToString("X");
          retString += " ";
        }
        return retString;
      }
      else if (varaint == "ASCII")
      {
        string retString = string.Empty;
        foreach (var data in _reciveData)
        {
          if (data >= 0x21 && data <= 0x7F)
          {
            retString += data.ToString();
            retString += " ";
          }
          else
          {
            retString += ". ";
          }
        }

        return retString;
      }
      else
      {
        return String.Empty;
      }
    }

    //  -- START: Parss methods --
    private String parsCanAddres()
    {
      return ((_reciveData[0] << 3) + ((_reciveData[1] & 0b11100000) >> 5)).ToString("X");
    }

    private String parsRTR()
    {
      return ((_reciveData[1] & 0b00010000) >> 4).ToString("X");
    }

    private String ParsIDE()
    {
      return ((_reciveData[1] & 0b00001000) >> 3).ToString("X");
    }

    private String ParsDLC()
    {
      return (_reciveData[1] & 0b00000111).ToString("X");
    }

    private String ParsData()
    {
      String retData = String.Empty;

      for (int i = 2; i < 2 + Convert.ToInt32(DLC, 16) ; i++)
      {
        retData += $"{_reciveData[i].ToString("X")} ";
      }

      return retData;

    } //  -- END OF: Parss methods --  
  }
}
