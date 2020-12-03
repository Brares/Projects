using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BaseLayerObjects
{
    public class OrderBase
    {
        public int OrderID { get; set; }
        public string CustomerID { get; set; }
        public int?  EmployeeID { get; set; }
        public DateTime OrderDate { get; set; }
        public DateTime? RequiredDate { get; set; }
        public DateTime? ShippedDate { get; set; }
        public int? ShipVia { get; set; }
        public decimal? Freight { get; set; }
        public string ShipName { get; set; }
        public string ShipAddress { get; set; }
        public string ShipCity { get; set; }
        public string ShipRegion { get; set; }
        public string ShipPostalCode { get; set; }
        public string ShipCountry { get; set; }
        List<OrderDetailsBase> mListOrderDetailsBase = new List<OrderDetailsBase>();
        public OrderBase()
        { }

        public OrderBase(
            int orderID,
            string customerID,
            int employeeID,
            DateTime orderDate,
            DateTime? requiredDate,
            DateTime? shippedDate,
            int? shipVia,
            decimal? freight,
            string shipName,
            string shipAddress,
            string shipCity,
            string shipRegion,
            string shipPostalCode,
            string shipCountry
            )
        {
            this.OrderID = orderID;
            this.CustomerID = customerID;
            this.EmployeeID = employeeID;
            this.OrderDate = orderDate;
            this.RequiredDate = requiredDate;
            this.ShippedDate = shippedDate;
            this.ShipVia = shipVia;
            this.Freight = freight;
            this.ShipName = shipName;
            this.ShipAddress = shipAddress;
            this.ShipCity = shipCity;
            this.ShipRegion = ShipRegion;
            this.ShipPostalCode = shipPostalCode;
            this.ShipCountry = shipCountry;
        }

        public List<OrderDetailsBase> ListOrderDetailsBase {
            get { return mListOrderDetailsBase; }
            set { mListOrderDetailsBase = value; }
        } //this will make it easier for the Business Layer to give the database layer new orders with all their details contained inside

    }
}
