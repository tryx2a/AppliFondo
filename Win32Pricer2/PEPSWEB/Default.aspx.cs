using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using Wrapper2;

namespace PEPSWEB
{
    public partial class _Default : Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }

        protected void simul_Click(object sender, EventArgs e)
        {
            double V;

            int timeStepSub = Convert.ToInt32(HttpContext.Current.Application["timeStepSub"]);
            int H = Convert.ToInt32(HttpContext.Current.Application["H"]);
            int samples = Convert.ToInt32(HttpContext.Current.Application["TourMC"]);

            WrapperClass2 wc = new WrapperClass2(timeStepSub,H,samples);

            wc.computeCompoPfWrapper(3.1);
            V = wc.getPartSansRisqueWrapper();

            double[] delta = wc.getVectDelta();

            deltaV.Text += "<table class=\"table\"><tr><th>Titres</th><th>Valeur</th></tr>";
            for (int i = 0; i < delta.Length; i++)
            {
                deltaV.Text += "<tr><td> Titre " + i + "</td><td>" + delta[i].ToString() + "</td></tr>";
            }
            deltaV.Text += "</table>";

            sansRisque.Text = V.ToString();
        }
    }
}