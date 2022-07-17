using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CanAnalyzer.Model
{
  public class Analyzer
  {
    public List<Frame> FramesList;

    public Analyzer()
    {
      FramesList = new List<Frame>();
    }

    void addFrame(byte[] dataframe, String strimeDirection)
    {
      FramesList.Add(new Frame(dataframe));
    }
  }
}
