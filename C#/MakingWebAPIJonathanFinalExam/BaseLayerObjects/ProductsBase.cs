using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BaseLayerObjects
{
    public class ProductsBase
    {
        public int ProductID { get; set; }
        public string ProductName { get; set; }
        public int? SupplierID { get; set; }
        public int? CategoryID { get; set; }
        public string QuantityPerUnit { get; set; }
        public decimal? UnitPrice { get; set; }
        public short? UnitsInStock { get; set; }
        public short? UnitsOnOrder { get; set; }
        public short? ReorderLevel { get; set; }
        public bool Discontinued { get; set; }

        public static ProductsBase GetProduct(string ProductID)
        {
            // will retrieve information from the DB and return a Order Details object matching what it found in the DB

            throw new NotImplementedException();

        }

        public ProductsBase()
        { }
        public ProductsBase(
         int ProductID,
         string ProductName,
         int? SupplierID,
         int? CategoryID,
         string QuantityPerUnit,
         decimal? UnitPrice,
         short? UnitsInStock,
         short? UnitsOnOrder,
         short? ReorderLevel,
         bool Discontinued)
        {
            this.ProductID = ProductID;
            this.ProductName = ProductName;
            this.SupplierID = SupplierID;
            this.CategoryID = CategoryID;
            this.QuantityPerUnit = QuantityPerUnit;
            this.UnitPrice = UnitPrice;
            this.UnitsInStock = UnitsInStock;
            this.UnitsOnOrder= UnitsOnOrder;
            this.ReorderLevel = ReorderLevel;
            this.Discontinued = Discontinued;
        }
    }
}

