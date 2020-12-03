using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using NwindAPI.Models;
using NWindDBLibrary;
using System.Data;

namespace NwindAPI.BusinessLayer
{
    public static partial class BLProduct
   {
        public static List<Product> ProductList()
        {
            List<Product> Productlist = new List<Product>();
            DataTable dtProducts = NWindDBLibrary.NwindDB.ProductTable();
            foreach (DataRow dr in dtProducts.Rows)
            {
                Product PB = new Product();
                PB.ProductID = (int)dr["ProductID"];
                PB.ProductName = (string)dr["ProductName"];
                PB.SupplierID = dr["SupplierID"] as int?;
                PB.CategoryID = dr["CategoryID"] as int?;
                PB.UnitPrice = dr["UnitPrice"] as decimal?;
                PB.QuantityPerUnit = dr["QuantityPerUnit"] as string;
                PB.UnitsInStock = dr["UnitsInStock"] as short?;
                PB.UnitsOnOrder = dr["UnitsOnOrder"] as short?;
                PB.ReorderLevel = dr["ReorderLevel"] as short?;
                PB.Discontinued = (bool)dr["Discontinued"];
                Productlist.Add(PB);
            }
            return Productlist;
        }

        public static Product GetProduct(int ProductID)
        {
            Product PB = null;
            DataRow dr = NwindDB.GetProduct(ProductID);
            if (dr != null)
            {
                PB = new Product();
                PB.ProductID = ProductID;
                PB.ProductName = (string)dr["ProductName"];
                PB.SupplierID = dr["SupplierID"] as int?;
                PB.CategoryID = dr["CategoryID"] as int?;
                PB.UnitPrice = dr["UnitPrice"] as decimal?;
                PB.QuantityPerUnit = dr["QuantityPerUnit"] as string;
                PB.UnitsInStock = dr["UnitsInStock"] as short?;
                PB.UnitsOnOrder = dr["UnitsOnOrder"] as short?;
                PB.ReorderLevel = dr["ReorderLevel"] as short?;
                PB.Discontinued = (bool)dr["Discontinued"];
            }
            return PB;
        }
    }
}