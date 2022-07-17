using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CanAnalyzer.Exceptions
{
  public class InvalidFrameException : Exception
  {
    string errorMesage { get; }

    public InvalidFrameException(string message)
    {
      errorMesage = message; 
    }
  }
}
