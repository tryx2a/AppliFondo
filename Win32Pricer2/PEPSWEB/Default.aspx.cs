using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using Wrapper2;
using PEPSWEB.ServiceReference1;

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
            //Récupération de la date
            string[] contentDateSelect = datepicker.Text.Split('/');
            int jour = Convert.ToInt32(contentDateSelect[0]);
            int mois = Convert.ToInt32(contentDateSelect[1]);
            int annee = Convert.ToInt32(contentDateSelect[2]);
            deltaV.Text = null;

            DateTime dateSelect = new DateTime(annee,mois,jour);

            DateTime datePrecedent = new DateTime(2015,03,03);

            DateTime debutSouscription = new DateTime(2011, 01, 29);
          
            //Calcul de la date à couvrir
            TimeSpan differenceJour = dateSelect.Subtract(debutSouscription);
            double tho = differenceJour.TotalDays / 365;

            double V;

            //Récupération des données de calculs
            int timeStepSub = Convert.ToInt32(HttpContext.Current.Application["timeStepSub"]);
            int H = Convert.ToInt32(HttpContext.Current.Application["H"]);
            int samples = Convert.ToInt32(HttpContext.Current.Application["TourMC"]);

            WrapperClass2 wc = new WrapperClass2(timeStepSub,H,samples);

            //Récupération des spots des actifs
            string[] symbole = { "BUD", "AAPL", "SAN", "3988.HK", "BRK.A", "0939.HK", "CHL", "ENI.MI", "XOM", "GSZ.PA", "1398.HK", "MC.PA",
                              "MSFT", "PTR", "SAN.PA", "SIE.DE", "TEF", "TOT", "UN", "WMT" };

            //Appel du service en ligne pour récupérer les spots
            ServiceReference1.ActifServiceClient client = new ServiceReference1.ActifServiceClient();
            ServiceReference1.DataHistoricalColumn[] hc = new ServiceReference1.DataHistoricalColumn[1];
            hc[0] = DataHistoricalColumn.Close;
            Data resultRq = client.getActifHistorique(symbole, hc, datePrecedent, datePrecedent);
            client.Close();

            //Affectation des valeurs
            double[] getSpot_ = new double[22];
            getSpot_[0] = 1.353;
            getSpot_[1] = 9.2362545;
            for (int i = 2; i < 22; i++)
            {
                getSpot_[i] = Convert.ToDouble(resultRq.Ds.Tables[0].Rows[i - 2]["Close"]);
            }

            wc.computeCompoPfWrapper(tho);
            V = wc.getPartSansRisqueWrapper();

            //Résultats des calculs et affichage
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