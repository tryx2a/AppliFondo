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
            if (string.IsNullOrWhiteSpace(datepicker.Text))
            {
                datepicker.Text = HttpContext.Current.Application["today"].ToString();
            }
        }

        protected void simul_Click(object sender, EventArgs e)
        {

            string[] contentDateSelect = datepicker.Text.Split('/');
            int jour = Convert.ToInt32(contentDateSelect[0]);
            int mois = Convert.ToInt32(contentDateSelect[1]);
            int annee = Convert.ToInt32(contentDateSelect[2]);

            deltaV.Text = null;

            DateTime dateSelect = new DateTime(annee,mois,jour);
            DateTime debutSouscription = new DateTime(2011, 01, 29);
          
            TimeSpan differenceJour = dateSelect.Subtract(debutSouscription);

            double tho = differenceJour.TotalDays / 365;

            double V;

            int timeStepSub = Convert.ToInt32(HttpContext.Current.Application["timeStepSub"]);
            int H = Convert.ToInt32(HttpContext.Current.Application["H"]);
            int samples = Convert.ToInt32(HttpContext.Current.Application["TourMC"]);

            WrapperClass2 wc = new WrapperClass2(timeStepSub,H,samples);

            wc.computeCompoPfWrapper(tho);
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