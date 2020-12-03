using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BaseLayerObjects
{
    public class OrderDetailsBase
    {
        public int OrderID { get; set; }
        public int ProductID { get; set; }
        public decimal UnitPrice { get; set; }
        public short Quantity { get; set; }
        public float Discount { get; set; }

        public static OrderDetailsBase GetOrderDetail(string OrderID) //may not need this**************
        {
            // will retrieve information from the DB and return a Order Details object matching what it found in the DB

            throw new NotImplementedException();

        }

        public OrderDetailsBase()
        { }
        public OrderDetailsBase(
         int OrderID,
         int ProductID,
         decimal UnitPrice,
         short Quantity,
         float Discount)
        {
            this.OrderID = OrderID;
            this.ProductID = ProductID;
            this.UnitPrice = UnitPrice;
            this.Quantity = Quantity;
            this.Discount = Discount;
        }
    }
}
