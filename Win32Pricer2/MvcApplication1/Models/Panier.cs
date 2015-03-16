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

        public List<Action> getListAction()
        {
            return new List<Action>
            {
                new Action {isin ="BE0003793107", nom = "Anheuser-Busch InBev NV", prix = 0},
                new Action {isin = "US0378331005", nom = "Apple Inc", prix = 0},
                new Action {isin = "ES0113900J37", nom = "Banco Santander SA", prix = 0},
                new Action {isin = "CNE1000001Z5", nom = "Bank of China Ltd", prix = 0},
                new Action {isin = "US0846707026", nom = "Berkshire Hathaway Inc", prix = 0},
                new Action {isin = "CNE1000002H1", nom = "China Construction Bank Corp", prix = 0},
                new Action {isin = "HK0941009539", nom = "China Mobile Ltd", prix = 0},
                new Action {isin = "IT0003132476", nom = "ENI SpA", prix = 0},
                new Action {isin = "US30231G1022", nom = "Exxon Mobil Corp", prix = 0},
                new Action {isin = "FR0010208488", nom = "GDF Suez", prix = 0},
                new Action {isin = "CNE1000003G1", nom = "Industrial & Commercial Bank of China", prix = 0},
                new Action {isin = "FR0000121014", nom = "LVMH", prix = 0},
                new Action {isin = "US5949181045", nom = "Microsoft Corp", prix = 0},
                new Action {isin = "CNE1000003W8", nom = "PetroChina Co Ltd", prix = 0},
                new Action {isin = "FR0000120578", nom = "Sanofi-Aventis SA", prix = 0},
                new Action {isin = "DE0007236101", nom = "Siemens AG", prix = 0},
                new Action {isin = "ES0178430E18", nom = "Telefonica SA", prix = 0},
                new Action {isin = "FR0000120271", nom = "Total SA", prix = 0},
                new Action {isin = "NL0000009355", nom = "Unilever NV", prix = 0},
                new Action {isin = "US9311421039", nom = "Wal-Mart Stores Inc", prix = 0}
            };
        }
    }
}