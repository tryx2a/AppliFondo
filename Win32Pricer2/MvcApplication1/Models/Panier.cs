using MvcApplication1.ServiceReference;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace MvcApplication1.Models
{
    public class Panier
    {
        public int taille { get; set; }
        public List<Action> listAction { get; set; }
        public double[] spot { get; set; }

        public double[] getSpot()
        {
            
            
            return spot;
        }

        public void setSpot(double[] spot_)
        {
            this.spot = spot_;
        }

        public List<Action> getListAction()
        {
            return new List<Action>
            {
                new Action {isin ="", nom = "Taux de change USD/EUR", prix = 0, devise="EUR (€)"},
                new Action {isin ="", nom = "Taux de change CNY/EUR", prix = 0, devise="EUR (€)"},
                new Action {isin ="BE0003793107", nom = "Anheuser-Busch InBev NV", prix = 0, devise="EUR (€)"},
                new Action {isin = "US0378331005", nom = "Apple Inc", prix = 0, devise="USD ($)"},
                new Action {isin = "ES0113900J37", nom = "Banco Santander SA", prix = 0, devise="EUR (€)"},
                new Action {isin = "CNE1000001Z5", nom = "Bank of China Ltd", prix = 0,devise="CNY (¥)"},
                new Action {isin = "US0846707026", nom = "Berkshire Hathaway Inc", prix = 0,devise="USD ($)"},
                new Action {isin = "CNE1000002H1", nom = "China Construction Bank Corp", prix = 0,devise="CNY (¥)"},
                new Action {isin = "HK0941009539", nom = "China Mobile Ltd", prix = 0,devise="CNY (¥)"},
                new Action {isin = "IT0003132476", nom = "ENI SpA", prix = 0,devise="EUR (€)"},
                new Action {isin = "US30231G1022", nom = "Exxon Mobil Corp", prix = 0,devise="USD ($)"},
                new Action {isin = "FR0010208488", nom = "GDF Suez", prix = 0,devise="EUR (€)"},
                new Action {isin = "CNE1000003G1", nom = "Industrial & Commercial Bank of China", prix = 0,devise="CNY (¥)"},
                new Action {isin = "FR0000121014", nom = "LVMH", prix = 0,devise="EUR (€)"},
                new Action {isin = "US5949181045", nom = "Microsoft Corp", prix = 0,devise="USD ($)"},
                new Action {isin = "CNE1000003W8", nom = "PetroChina Co Ltd", prix = 0,devise="CNY (¥)"},
                new Action {isin = "FR0000120578", nom = "Sanofi-Aventis SA", prix = 0,devise="EUR (€)"},
                new Action {isin = "DE0007236101", nom = "Siemens AG", prix = 0,devise="EUR (€)"},
                new Action {isin = "ES0178430E18", nom = "Telefonica SA", prix = 0,devise="EUR (€)"},
                new Action {isin = "FR0000120271", nom = "Total SA", prix = 0,devise="EUR (€)"},
                new Action {isin = "NL0000009355", nom = "Unilever NV", prix = 0,devise="EUR (€)"},
                new Action {isin = "US9311421039", nom = "Wal-Mart Stores Inc", prix = 0,devise="USD ($)"}
            };
        }
        /*
        public List<Action> getListAction(DateTime debut, DateTime fin)
        {

            string[] l = { "BUD", "AAPL", "SAN", "3988.HK", "BRK.A", "0939.HK", "CHL", "ENI.MI", "XOM", "GSZ.PA", "1398.HK", "MC.PA",
                              "MSFT", "PTR", "SAN.PA", "SIE.DE", "TEF", "TOT", "UN", "WMT" };

            //ServiceReference.ActifServiceClient client = new ServiceReference.ActifServiceClient();

            //ServiceReference.DataHistoricalColumn[] hc = new ServiceReference.DataHistoricalColumn[1];
            //hc[0] = DataHistoricalColumn.Close;

            //Data resultRq = client.getActifHistorique(l, hc, debut, fin);

            //client.Close();

            TauxDeChange fx = new TauxDeChange();

            double fxUsdEuro = fx.getFxUsdEur()[0];
            double fxCnyEuro = fx.getFxYuanEur()[0];


            double[] getSpot_ = new double[22];
            for (int i = 2; i < 22; i++)
            {
                getSpot_[i] = Convert.ToDouble(resultRq.Ds.Tables[0].Rows[i-2]["Close"]);
            }

            

                return new List<Action>
            {
                new Action {isin ="", nom = "Taux de change USD/EUR", prix = fxUsdEuro, devise="EUR (€)"},
                new Action {isin ="", nom = "Taux de change CNY/EUR", prix = fxCnyEuro, devise="EUR (€)"},
                new Action {isin ="BE0003793107", nom = "Anheuser-Busch InBev NV", prix = Convert.ToDouble(resultRq.Ds.Tables[0].Rows[0]["Close"]), devise="EUR (€)"},
                new Action {isin = "US0378331005", nom = "Apple Inc", prix = Convert.ToDouble(resultRq.Ds.Tables[0].Rows[1]["Close"]), devise="USD ($)"},
                new Action {isin = "ES0113900J37", nom = "Banco Santander SA", prix = Convert.ToDouble(resultRq.Ds.Tables[0].Rows[2]["Close"]), devise="EUR (€)"},
                new Action {isin = "CNE1000001Z5", nom = "Bank of China Ltd", prix = Convert.ToDouble(resultRq.Ds.Tables[0].Rows[3]["Close"]),devise="CNY (¥)"},
                new Action {isin = "US0846707026", nom = "Berkshire Hathaway Inc", prix = Convert.ToDouble(resultRq.Ds.Tables[0].Rows[4]["Close"]),devise="USD ($)"},
                new Action {isin = "CNE1000002H1", nom = "China Construction Bank Corp", prix = Convert.ToDouble(resultRq.Ds.Tables[0].Rows[5]["Close"]),devise="CNY (¥)"},
                new Action {isin = "HK0941009539", nom = "China Mobile Ltd", prix = Convert.ToDouble(resultRq.Ds.Tables[0].Rows[6]["Close"]),devise="CNY (¥)"},
                new Action {isin = "IT0003132476", nom = "ENI SpA", prix = Convert.ToDouble(resultRq.Ds.Tables[0].Rows[7]["Close"]),devise="EUR (€)"},
                new Action {isin = "US30231G1022", nom = "Exxon Mobil Corp", prix = Convert.ToDouble(resultRq.Ds.Tables[0].Rows[8]["Close"]),devise="USD ($)"},
                new Action {isin = "FR0010208488", nom = "GDF Suez", prix = Convert.ToDouble(resultRq.Ds.Tables[0].Rows[9]["Close"]),devise="EUR (€)"},
                new Action {isin = "CNE1000003G1", nom = "Industrial & Commercial Bank of China", prix = Convert.ToDouble(resultRq.Ds.Tables[0].Rows[10]["Close"]),devise="CNY (¥)"},
                new Action {isin = "FR0000121014", nom = "LVMH", prix = Convert.ToDouble(resultRq.Ds.Tables[0].Rows[11]["Close"]),devise="EUR (€)"},
                new Action {isin = "US5949181045", nom = "Microsoft Corp", prix = Convert.ToDouble(resultRq.Ds.Tables[0].Rows[12]["Close"]),devise="USD ($)"},
                new Action {isin = "CNE1000003W8", nom = "PetroChina Co Ltd", prix = Convert.ToDouble(resultRq.Ds.Tables[0].Rows[13]["Close"]),devise="CNY (¥)"},
                new Action {isin = "FR0000120578", nom = "Sanofi-Aventis SA", prix = Convert.ToDouble(resultRq.Ds.Tables[0].Rows[14]["Close"]),devise="EUR (€)"},
                new Action {isin = "DE0007236101", nom = "Siemens AG", prix = Convert.ToDouble(resultRq.Ds.Tables[0].Rows[15]["Close"]),devise="EUR (€)"},
                new Action {isin = "ES0178430E18", nom = "Telefonica SA", prix =Convert.ToDouble(resultRq.Ds.Tables[0].Rows[16]["Close"]),devise="EUR (€)"},
                new Action {isin = "FR0000120271", nom = "Total SA", prix = Convert.ToDouble(resultRq.Ds.Tables[0].Rows[17]["Close"]),devise="EUR (€)"},
                new Action {isin = "NL0000009355", nom = "Unilever NV", prix = Convert.ToDouble(resultRq.Ds.Tables[0].Rows[18]["Close"]),devise="EUR (€)"},
                new Action {isin = "US9311421039", nom = "Wal-Mart Stores Inc", prix = Convert.ToDouble(resultRq.Ds.Tables[0].Rows[19]["Close"]),devise="USD ($)"}
            };
        }*/
    }

}