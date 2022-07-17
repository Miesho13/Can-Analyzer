using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CanAnalyzer.Model
{
  public class SetDataForSend
  {
    public int FilterID { get; set; }
    public int FilterMaskID { get; set; }
    public int CanBaudRate { get; set; }
    public SetDataForSend(int filterID, int filterMaskID, int canBaudRate)
    {
      FilterID = filterID;
      FilterMaskID = filterMaskID;
      CanBaudRate = canBaudRate;
    }

    public byte[] Send()
    {
      byte[] toSend = new byte[7];
      switch (CanBaudRate)
      {
        case 0:
          toSend[0] = 18;
          toSend[1] = 11;
          toSend[2] = 8;
          break;

        case 1:
          toSend[0] = 18;
          toSend[1] = 7;
          toSend[2] = 8;
          break;

        case 2:
          toSend[0] = 9;
          toSend[1] = 7;
          toSend[2] = 8;
          break;

        case 3:
          toSend[0] = 4;
          toSend[1] = 9;
          toSend[2] = 8;
          break;
      }

      toSend[3]= (byte)((FilterID & 0b1111111100000000) >> 8);
      toSend[4] = (byte)(FilterID & 0b0000000011111111);
      
      toSend[5] = (byte)((FilterMaskID & 0b1111111100000000) >> 8);
      toSend[6] = (byte)(FilterMaskID & 0b0000000011111111);

      return toSend;
    }
  }
}
