using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using Wrapper2;
using PEPSWEB.ServiceReference1;
using PEPSWEB.Models;

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
            try
            {
                //Récupération de la date
                string[] contentDateSelect = datepicker.Text.Split('/');
                int jour = Convert.ToInt32(contentDateSelect[0]);
                int mois = Convert.ToInt32(contentDateSelect[1]);
                int annee = Convert.ToInt32(contentDateSelect[2]);

                //Efface les résultats de l'affichage
                deltaV.Text = null;
                sansRisque.Text = null;

                //Création des dates du produits
                DateTime dateSelect = new DateTime(annee, mois, jour);
                DateTime debutSouscription = new DateTime(2011, 01, 29);

                //Calcul de la date à couvrir
                TimeSpan differenceJour = dateSelect.Subtract(debutSouscription);
                double tho = differenceJour.TotalDays / 365;

                double V;

                //Récupération des données de calculs
                int timeStepSub = Convert.ToInt32(HttpContext.Current.Application["timeStepSub"]);
                int H = Convert.ToInt32(HttpContext.Current.Application["H"]);
                int samples = Convert.ToInt32(HttpContext.Current.Application["TourMC"]);

                WrapperClass2 wc = new WrapperClass2(timeStepSub, H, samples);

                if (CheckBox1.Checked)
                {
                    //Récupération des spots des actifs
                    string[] symbole = { "BUD", "SAN", "ENI.MI", "GSZ.PA", "MC.PA","SAN.PA", "SIE.DE", "TEF", "TOT", "UN",
                                         "AAPL", "BRK.A","XOM","MSFT", "WMT" ,"3988.HK","0939.HK", "CHL", "1398.HK", "PTR"};

                    //Appel du service en ligne pour récupérer les spots
                    ServiceReference1.ActifServiceClient client = new ServiceReference1.ActifServiceClient();
                    ServiceReference1.DataHistoricalColumn[] hc = new ServiceReference1.DataHistoricalColumn[1];
                    hc[0] = DataHistoricalColumn.Close;
                    Data resultRq = client.getActifHistorique(symbole, hc, debutSouscription, debutSouscription);
                    client.Close();

                    //Affectation des valeurs
                    wc.setSpot(1.353,0);
                    wc.setSpot(9.2362545, 1);
                    for (int i = 2; i < 22; i++)
                    {
                        wc.setSpot(Convert.ToDouble(resultRq.Ds.Tables[0].Rows[i - 2]["Close"]),i);
                    }
                   

                }
                
                

                wc.computeCompoPfWrapper(tho);
                V = wc.getPartSansRisqueWrapper();

                //Résultats des calculs et affichage
                double[] delta = wc.getVectDelta();
                Panier p = new Panier();
                List<PEPSWEB.Models.Action> listAction = p.getListAction();

               
                deltaV.Text += "<p> Part à investir dans chaque titre : </p>" + "<table class=\"table\"><tr><th>Titres</th><th>Valeur</th></tr>";

                int cmp = 0;
                foreach (PEPSWEB.Models.Action action in listAction)
                {
                    deltaV.Text += "<tr><td>"+ action.nom + "</td><td>" + delta[cmp].ToString() + "</td></tr>";
                    cmp++;
                }
               
                /*for (int i = 0; i < delta.Length; i++)
                {
                    deltaV.Text += "<tr><td> Titre " + i + "</td><td>" + delta[i].ToString() + "</td></tr>";
                }*/
                deltaV.Text += "</table>";
                sansRisque.Text = "Part à investir au taux sans risque : " + V.ToString();
            }
            catch (InvalidOperationException ioe)
            {
                MessageBox.Show("La simulation a échoué");
                Console.WriteLine("Michel");
            }
        }
    }
}