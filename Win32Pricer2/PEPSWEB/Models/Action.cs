using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace PEPSWEB.Models
{
    public class Action
    {
        public string isin { get; set; }
        public string nom { get; set; }
        public double prix { get; set; }
        public string devise { get; set; }
        public double delta { get; set; }
    }
}