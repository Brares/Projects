using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace WebApplication1.Models
{
    public class Shipper
    {
        public static List<Shipper> TestList()
        {
            List<Shipper> shipperlist = new List<Shipper>();
            Shipper s1 = new Shipper();
            s1.ShipperID = 1;
            s1.CompanyName = "Shipper1";
            s1.Phone = "111-111-1111";
            shipperlist.Add(s1);
            Shipper s2 = new Shipper();
            s2.ShipperID = 2;
            s2.CompanyName = "Shipper2";
            s2.Phone = "222-222-2222";
            shipperlist.Add(s2);
            return shipperlist;
        }
        public int ShipperID { get; set; }
        public string CompanyName { get; set; }
        public string Phone { get; set; }
    }
}