using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace MvcApplication1.Models
{
    public class TauxDeChange
    {
        public double[] fxUsdEur { get; set; }
        public double[] fxYuanEur { get; set; }

        public double[] getFxUsdEur()
        {
            double[] fxUSDEUR = { 1.353, 1.2369, 1.3095, 1.3973, 1.3171, 1.4141, 1.4287, 1.4242, 1.3672, 1.293, 1.3171, 1.2518,
                              1.2422, 1.3106, 1.3195, 1.3076, 1.292, 1.3296, 1.3664, 1.3779, 1.3924, 1.3628, 1.3366, 1.2812, 1.2101, 1.0575 };

            return fxUSDEUR;
        }

        public double[] getFxYuanEur()
        {
            double[] fxCNYEUR = { 9.2362545, 8.44864545, 8.867934, 9.29232446, 8.6731035, 9.28908149, 9.2751204, 9.15817568, 8.726154,
                                    8.1382713, 8.32696962, 7.94129402, 7.90834208, 8.19138106, 8.22061695, 8.12451108, 7.9213812, 8.1391464,
                                    8.3323072, 8.34139323, 8.56326, 8.49882964, 8.2474903, 7.8447876, 7.50818646, 6.622065 };
            return fxCNYEUR;
        }
    }
}