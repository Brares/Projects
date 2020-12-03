using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Data;
using System.Data.SqlClient;
using System.Configuration;
using BaseLayerObjects;
namespace NWindDBLibrary
{
    public static class NwindDB
    {
        private static string ConString = "server=b231-inst;database=NwindSQL3;integrated security=true;timeout=4";
        //getting the connection string from the config file
        //note you have to add a reference to System.Configuration and a Using statement

        //private static string ConString = ConfigurationManager.ConnectionStrings["B231InstructorMachine"].ConnectionString;

        private static SqlConnection con;
        public static void TestConnection()
        {
            OpenDB();
            CloseDB();
        }
        private static void OpenDB()
        {
            if (con == null)
                con = new SqlConnection(ConString);
            if (con.State != System.Data.ConnectionState.Open)
                con.Open();
        }
        private static void CloseDB()
        {
            if (con != null)
                if (con.State == System.Data.ConnectionState.Open)
                    con.Close();

        }

        public static void SaveNewCustomer(CustomerBase C)
        {
            //It would be better to use parameters, and also this will crash if any of the string fields are null
            //(This is also dangerous in that it allows for possibility of SQL injection! 
            SqlCommand cmd = new SqlCommand($"Insert Into Customers (CustomerID, CompanyName, ContactName, ContactTitle, Address, City, Region, PostalCode, Country, Phone, Fax) Values ('{C.CustomerID}', '{C.CompanyName.Replace("'", "''")}', '{C.ContactName}', '{C.ContactTitle}', '{C.Address}', '{C.City}', '{C.Region}', '{C.PostalCode}', '{C.Country}', '{C.Phone}', '{C.Fax}' )");
            OpenDB();
            cmd.Connection = con;
            cmd.ExecuteNonQuery();
            CloseDB();
        }

        public static List<CustomerBase> AllCustomers() //return a list of all customers stored as CustomerBase objects
        {
            List<CustomerBase> CustList = new List<CustomerBase>();
            DataTable dtCustomers = Customer(); //I just used the method that Jayden had made to return the datatable
            CustomerBase C;
            foreach (DataRow dr in dtCustomers.Rows)
            {
                C = new CustomerBase();
                C.CustomerID = (string)dr["CustomerID"];
                C.CompanyName = (string)dr["CompanyName"];
                C.ContactName = dr["ContactName"] != DBNull.Value ? (string)dr["ContactName"] : null;
                C.ContactTitle = dr["ContactTitle"] != DBNull.Value ? (string)dr["ContactTitle"] : null;
                C.Address = dr["Address"] != DBNull.Value ? (string)dr["Address"] : null;
                C.City = dr["City"] != DBNull.Value ? (string)dr["City"] : null;
                C.Region = dr["Region"] != DBNull.Value ? (string)dr["Region"] : null;
                C.PostalCode = dr["PostalCode"] != DBNull.Value ? (string)dr["PostalCode"] : null;
                C.Country = dr["Country"] != DBNull.Value ? (string)dr["Country"] : null;
                C.Phone = dr["Phone"] != DBNull.Value ? (string)dr["Phone"] : null;
                C.Fax = dr["Fax"] != DBNull.Value ? (string)dr["Fax"] : null;
                CustList.Add(C);
            }
            return CustList;
        }

        public static List<OrderBase> OrdersForCustomer(string CustomerID)
        {
            List<OrderBase> CustOrders = new List<OrderBase>();
            OrderBase OB;
            OrderDetailsBase ODB;
            DataTable dtOrders = new DataTable(), dtDetails;
            //get the orders
            string sql = "Select * from Orders where CustomerID = @CustomerID order by OrderDate";
            string sqlDet = "Select * from [Order Details] Where OrderID = @OrderID";
            SqlDataAdapter da, daDet;
            OpenDB();
            da = new SqlDataAdapter(sql, con);
            da.SelectCommand.Parameters.Add(new SqlParameter("@CustomerID", CustomerID));
            da.FillSchema(dtOrders, SchemaType.Source);
            da.Fill(dtOrders);
            foreach (DataRow dr in dtOrders.Rows)
            {
                OB = new OrderBase();
                OB.OrderID = (int)dr["OrderID"];
                OB.CustomerID = CustomerID;
                OB.OrderDate = (DateTime)dr["OrderDate"];
                OB.RequiredDate = dr["RequiredDate"] != DBNull.Value ? (DateTime?)dr["RequiredDate"] : null;
                OB.ShippedDate = dr["ShippedDate"] != DBNull.Value ? (DateTime?)dr["ShippedDate"] : null;
                OB.EmployeeID = dr["EmployeeID"] != DBNull.Value ? (int?)dr["EmployeeID"] : null;
                OB.ShipVia = dr["ShipVia"] != DBNull.Value ? (int?)dr["ShipVia"] : null;
                OB.Freight = dr["Freight"] != DBNull.Value ? (decimal?)dr["Freight"] : null;
                OB.ShipName = dr["ShipName"] != DBNull.Value ? (string)dr["ShipName"] : null;
                OB.ShipAddress = dr["ShipAddress"] != DBNull.Value ? (string)dr["ShipAddress"] : null;
                OB.ShipCity = dr["ShipCity"] != DBNull.Value ? (string)dr["ShipCity"] : null;
                OB.ShipRegion = dr["ShipRegion"] != DBNull.Value ? (string)dr["ShipRegion"] : null;
                OB.ShipPostalCode = dr["ShipPostalCode"] != DBNull.Value ? (string)dr["ShipPostalCode"] : null;
                OB.ShipCountry = dr["ShipCountry"] != DBNull.Value ? (string)dr["ShipCountry"] : null;

                //and now get all the details for the  order 
                daDet = new SqlDataAdapter(sqlDet, con);
                daDet.SelectCommand.Parameters.Add(new SqlParameter("@OrderID", OB.OrderID));
                dtDetails = new DataTable(); //must make a new one or it will add on to the old one!
                daDet.FillSchema(dtDetails, SchemaType.Source);
                daDet.Fill(dtDetails);
                OB.ListOrderDetailsBase = new List<OrderDetailsBase>();
                foreach (DataRow drdet in dtDetails.Rows)
                {
                    ODB = new OrderDetailsBase();
                    ODB.OrderID = OB.OrderID;
                    ODB.ProductID = (int)drdet["ProductID"];
                    ODB.UnitPrice = (decimal)drdet["UnitPrice"];
                    ODB.Quantity = (short)drdet["Quantity"];
                    ODB.Discount = (float)drdet["Discount"];
                    OB.ListOrderDetailsBase.Add(ODB);
                }
                CustOrders.Add(OB);
            }
            return CustOrders;
        }

        public static DataTable Customer() //could make this private in the future
        {
            DataTable dtCustomer = new DataTable();
            string sql = "SELECT * FROM Customers";
            SqlDataAdapter da;
            OpenDB();
            da = new SqlDataAdapter(sql, con);
            da.FillSchema(dtCustomer, SchemaType.Source);
            da.Fill(dtCustomer);
            CloseDB();
            return dtCustomer;
        }

        public static CustomerBase GetCustomer(string customerID)
        {
            CustomerBase customer = new CustomerBase();
            DataTable dtCustomers = new DataTable();
            string sql = $"Select * From Customers Where CustomerID= '{customerID}'";
            SqlDataAdapter da;
            OpenDB();
            da = new SqlDataAdapter(sql, con);
            da.FillSchema(dtCustomers, SchemaType.Source);
            da.Fill(dtCustomers);
            CloseDB();
            DataRow CurrentRow = dtCustomers.Rows[0];
            customer.CustomerID = CurrentRow["CustomerID"].ToString();
            customer.CompanyName = CurrentRow["CompanyName"].ToString();
            customer.ContactName = CurrentRow["ContactName"].ToString();
            customer.ContactTitle = CurrentRow["ContactTitle"].ToString();
            customer.Address = CurrentRow["Address"].ToString();
            customer.City = CurrentRow["City"].ToString();
            customer.Region = CurrentRow["Region"].ToString();
            customer.PostalCode = CurrentRow["PostalCode"].ToString();
            customer.Country = CurrentRow["Country"].ToString();
            customer.Phone = CurrentRow["Phone"].ToString();
            customer.Fax = CurrentRow["Fax"].ToString();
            return customer;
        }
        public static DataTable ProductTable()
        {
            DataTable dtProducts = new DataTable();
            string sql = "SELECT * FROM Products Order by ProductName";
            SqlDataAdapter da;
            OpenDB();
            da = new SqlDataAdapter(sql, con);
            da.FillSchema(dtProducts, SchemaType.Source);
            da.Fill(dtProducts);
            CloseDB();
            return dtProducts;
        }
        public static List<ProductsBase> ProductList()
        {
            List<ProductsBase> PBList = new List<ProductsBase>();
            foreach (DataRow dr in ProductTable().Rows) //use the ProductTable method above
            {
                ProductsBase PB = new ProductsBase();
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
                PBList.Add(PB);
            }
            return PBList;
        }

        public static DataTable CategoryDropTable()
        {
            DataTable dtCategories = new DataTable();
            string sql = "SELECT CategoryID, CategoryName FROM Categories";
            SqlDataAdapter da;
            OpenDB();
            da = new SqlDataAdapter(sql, con);
            da.FillSchema(dtCategories, SchemaType.Source);
            da.Fill(dtCategories);
            CloseDB();

            return dtCategories;
        }

        public static DataTable ListOfOrders(CustomerBase C)
        {
            DataTable dtOrders = new DataTable();
            string sql = $"Select * From Orders Where CustomerID = '{C.CustomerID}' Order by OrderDate Desc";
            SqlDataAdapter da;
            OpenDB();
            da = new SqlDataAdapter(sql, con);
            da.FillSchema(dtOrders, SchemaType.Source);
            da.Fill(dtOrders);
            CloseDB();

            return dtOrders;
        }

        public static DataTable CustomerDropTable()
        {
            DataTable dtCustomers = new DataTable();
            string sql = "SELECT CustomerID, CompanyName FROM Customers";
            SqlDataAdapter da;
            OpenDB();
            da = new SqlDataAdapter(sql, con);
            da.FillSchema(dtCustomers, SchemaType.Source);
            da.Fill(dtCustomers);
            CloseDB();
            return dtCustomers;
        }

        public static void AddNewProduct(string ProductName, object CategoryID, object SupplierID, object UnitPrice)
        {
            // ProductName = ProductName.Replace("'","''"); //say goodbye to this  say hello to using parameters

            string sql = "INSERT INTO Products (ProductName, CategoryID, SupplierID, UnitPrice) values (@ProductName, @CategoryID, @SupplierID, @UnitPrice)";

            SqlCommand cmd = new SqlCommand(sql, con);
            OpenDB();
            cmd.Parameters.Add(new SqlParameter("@ProductName", ProductName));
            if (CategoryID == DBNull.Value)
                cmd.Parameters.Add(new SqlParameter("@CategoryID", DBNull.Value));
            else
                cmd.Parameters.Add(new SqlParameter("@CategoryID", (int)CategoryID));
            if (SupplierID == DBNull.Value)
                cmd.Parameters.Add(new SqlParameter("@SupplierID", DBNull.Value));
            else
                cmd.Parameters.Add(new SqlParameter("@SupplierID", (int)SupplierID));
            if (UnitPrice == DBNull.Value)
                cmd.Parameters.Add(new SqlParameter("@UnitPrice", DBNull.Value));
            else
                cmd.Parameters.Add(new SqlParameter("@UnitPrice", (decimal)UnitPrice));

            cmd.ExecuteNonQuery();
            CloseDB();

        }
        public static int StockDelivered(int CategoryID) //will update stock for category and return the number or rows actually changed
        {
            int RowsChanged;
            SqlCommand cmd = new SqlCommand("ReceiveStockForCategory", con); //use SPROC that Mark made
            cmd.CommandType = CommandType.StoredProcedure;
            OpenDB();
            SqlParameter returnparam = new SqlParameter();
            returnparam.Direction = ParameterDirection.ReturnValue;
            cmd.Parameters.Add(returnparam);
            cmd.Parameters.Add(new SqlParameter("@CategoryID", CategoryID)); //this has to agree with the SPROC
            cmd.ExecuteNonQuery();
            CloseDB(); //close db - thanks Brandon K
            RowsChanged = (int)cmd.Parameters[0].Value;
            //or could do this: RowsChanged = (int)returnparam.Value;
            return RowsChanged;
        }

        public static int AddNewOrder(OrderBase NewOrder) //Save new order and return new OrderId 
                                                          // will use a transaction to add a new order together with all it's details
        {
            SqlCommand cmd = new SqlCommand($"Insert Into Orders(CustomerID, EmployeeID, OrderDate, RequiredDate, ShippedDate, ShipVia, Freight, ShipName, ShipAddress, ShipCity, ShipRegion, ShipPostalCode, ShipCountry) Values (@CustomerID, @EmployeeID, @OrderDate, @RequiredDate, @ShippedDate, @ShipVia, @Freight, @ShipName, @ShipAddress, @ShipCity ,@ShipRegion, @ShipPostalCode, @ShipCountry)");
            OpenDB();
            SqlTransaction Trans = con.BeginTransaction();
            cmd.Connection = con;
            cmd.Transaction = Trans;

            cmd.Parameters.Add(new SqlParameter("@CustomerID", NewOrder.CustomerID));

            if (NewOrder.EmployeeID != null)
                cmd.Parameters.Add(new SqlParameter("@EmployeeID", NewOrder.EmployeeID));
            else
                cmd.Parameters.Add(new SqlParameter("@EmployeeID", DBNull.Value));

            cmd.Parameters.Add(new SqlParameter("@OrderDate", NewOrder.OrderDate));

            if (NewOrder.RequiredDate != null)
                cmd.Parameters.Add(new SqlParameter("@RequiredDate", NewOrder.RequiredDate));
            else
                cmd.Parameters.Add(new SqlParameter("@RequiredDate", DBNull.Value));

            if (NewOrder.ShippedDate != null)
                cmd.Parameters.Add(new SqlParameter("@ShippedDate", NewOrder.ShippedDate));
            else
                cmd.Parameters.Add(new SqlParameter("@ShippedDate", DBNull.Value));

            if (NewOrder.ShipVia != null)
                cmd.Parameters.Add(new SqlParameter("@ShipVia", NewOrder.ShipVia));
            else
                cmd.Parameters.Add(new SqlParameter("@ShipVia", DBNull.Value));

            if (NewOrder.Freight != null)
                cmd.Parameters.Add(new SqlParameter("@Freight", NewOrder.Freight));
            else
                cmd.Parameters.Add(new SqlParameter("@Freight", DBNull.Value));

            if (NewOrder.ShipName != null)
                cmd.Parameters.Add(new SqlParameter("@ShipName", NewOrder.ShipName));
            else
                cmd.Parameters.Add(new SqlParameter("@ShipName", DBNull.Value));

            if (NewOrder.ShipAddress != null)
                cmd.Parameters.Add(new SqlParameter("@ShipAddress", NewOrder.ShipAddress));
            else
                cmd.Parameters.Add(new SqlParameter("@ShipAddress", DBNull.Value));

            if (NewOrder.ShipCity != null)
                cmd.Parameters.Add(new SqlParameter("@ShipCity", NewOrder.ShipCity));
            else
                cmd.Parameters.Add(new SqlParameter("@ShipCity", DBNull.Value));

            if (NewOrder.ShipRegion != null)
                cmd.Parameters.Add(new SqlParameter("@ShipRegion", NewOrder.ShipRegion));
            else
                cmd.Parameters.Add(new SqlParameter("@ShipRegion", DBNull.Value));

            if (NewOrder.ShipPostalCode != null)
                cmd.Parameters.Add(new SqlParameter("@ShipPostalCode", NewOrder.ShipPostalCode));
            else
                cmd.Parameters.Add(new SqlParameter("@ShipPostalCode", DBNull.Value));

            if (NewOrder.ShipCountry != null)
                cmd.Parameters.Add(new SqlParameter("@ShipCountry", NewOrder.ShipCountry));
            else
                cmd.Parameters.Add(new SqlParameter("@ShipCountry", DBNull.Value));

            //try
            //{
                cmd.ExecuteNonQuery();
                SqlCommand cmd2 = new SqlCommand("select max(orderid) from Orders", con);
                cmd2.Transaction = Trans;
                int OrderID = (int)cmd2.ExecuteScalar();
                foreach (OrderDetailsBase odb in NewOrder.ListOrderDetailsBase)
                {
                    SqlCommand cmd3 = new SqlCommand("Insert Into [Order Details](OrderID, ProductID, UnitPrice, Quantity, Discount) Values (@OrderID, @ProductID, @UnitPrice, @Quantity, @Discount)" , con);
                    cmd3.Parameters.Add(new SqlParameter("@OrderID", OrderID));
                    cmd3.Parameters.Add(new SqlParameter("@ProductID", odb.ProductID));
                    cmd3.Parameters.Add(new SqlParameter("@UnitPrice", odb.UnitPrice));
                    cmd3.Parameters.Add(new SqlParameter("@Quantity", odb.Quantity));
                    cmd3.Parameters.Add(new SqlParameter("@Discount", odb.Discount));
                    cmd3.Transaction = Trans;
                    cmd3.ExecuteNonQuery();
                }
                Trans.Commit(); // Commit the transaction
                CloseDB();
                NewOrder.OrderID = OrderID;
                foreach (OrderDetailsBase odb in NewOrder.ListOrderDetailsBase)
                {
                    odb.OrderID = OrderID;
                }
                return OrderID;
            //}
            //catch (Exception ex)
            //{
            //    Trans.Rollback();
            //    CloseDB();
            //    throw ex;
            //}
        }

        public static void UpdateOrder(OrderBase TheOrder)
        {
            SqlCommand cmd = new SqlCommand($"UPDATE Orders SET CustomerID = @CustomerID, EmployeeID = @EmployeeID, OrderDate = @OrderDate, RequiredDate = @RequiredDate, ShippedDate = @ShippedDate, ShipVia = @ShipVia, Freight = @Freight, ShipName = @ShipName, ShipAddress = @ShipAddress, ShipCity = @ShipCity, ShipRegion = @ShipRegion, ShipPostalCode = @ShipPostalCode, ShipCountry = @ShipCountry WHERE OrderID = @OrderID");
            OpenDB();
            SqlTransaction Trans = con.BeginTransaction();
            cmd.Connection = con;
            cmd.Transaction = Trans;

            cmd.Parameters.Add(new SqlParameter("@OrderID", TheOrder.OrderID));
            cmd.Parameters.Add(new SqlParameter("@CustomerID", TheOrder.CustomerID));

            if (TheOrder.EmployeeID != null)
                cmd.Parameters.Add(new SqlParameter("@EmployeeID", TheOrder.EmployeeID));
            else
                cmd.Parameters.Add(new SqlParameter("@EmployeeID", DBNull.Value));

            cmd.Parameters.Add(new SqlParameter("@OrderDate", TheOrder.OrderDate));

            if (TheOrder.RequiredDate != null)
                cmd.Parameters.Add(new SqlParameter("@RequiredDate", TheOrder.RequiredDate));
            else
                cmd.Parameters.Add(new SqlParameter("@RequiredDate", DBNull.Value));

            if (TheOrder.ShippedDate != null)
                cmd.Parameters.Add(new SqlParameter("@ShippedDate", TheOrder.ShippedDate));
            else
                cmd.Parameters.Add(new SqlParameter("@ShippedDate", DBNull.Value));

            if (TheOrder.ShipVia != null)
                cmd.Parameters.Add(new SqlParameter("@ShipVia", TheOrder.ShipVia));
            else
                cmd.Parameters.Add(new SqlParameter("@ShipVia", DBNull.Value));

            if (TheOrder.Freight != null)
                cmd.Parameters.Add(new SqlParameter("@Freight", TheOrder.Freight));
            else
                cmd.Parameters.Add(new SqlParameter("@Freight", DBNull.Value));

            if (TheOrder.ShipName != null)
                cmd.Parameters.Add(new SqlParameter("@ShipName", TheOrder.ShipName));
            else
                cmd.Parameters.Add(new SqlParameter("@ShipName", DBNull.Value));

            if (TheOrder.ShipAddress != null)
                cmd.Parameters.Add(new SqlParameter("@ShipAddress", TheOrder.ShipAddress));
            else
                cmd.Parameters.Add(new SqlParameter("@ShipAddress", DBNull.Value));

            if (TheOrder.ShipCity != null)
                cmd.Parameters.Add(new SqlParameter("@ShipCity", TheOrder.ShipCity));
            else
                cmd.Parameters.Add(new SqlParameter("@ShipCity", DBNull.Value));

            if (TheOrder.ShipRegion != null)
                cmd.Parameters.Add(new SqlParameter("@ShipRegion", TheOrder.ShipRegion));
            else
                cmd.Parameters.Add(new SqlParameter("@ShipRegion", DBNull.Value));

            if (TheOrder.ShipPostalCode != null)
                cmd.Parameters.Add(new SqlParameter("@ShipPostalCode", TheOrder.ShipPostalCode));
            else
                cmd.Parameters.Add(new SqlParameter("@ShipPostalCode", DBNull.Value));

            if (TheOrder.ShipCountry != null)
                cmd.Parameters.Add(new SqlParameter("@ShipCountry", TheOrder.ShipCountry));
            else
                cmd.Parameters.Add(new SqlParameter("@ShipCountry", DBNull.Value));

            cmd.ExecuteNonQuery();
            SqlCommand cmd2 = new SqlCommand("Delete From [Order Details] Where OrderID = @OrderID", con);
            cmd2.Transaction = Trans;
            cmd2.Parameters.Add(new SqlParameter("@OrderID", TheOrder.OrderID));

            cmd2.ExecuteNonQuery();
            foreach (OrderDetailsBase odb in TheOrder.ListOrderDetailsBase)
            {
                SqlCommand cmd3 = new SqlCommand("Insert Into [Order Details](OrderID, ProductID, UnitPrice, Quantity, Discount) Values (@OrderID, @ProductID, @UnitPrice, @Quantity, @Discount)", con);
                cmd3.Parameters.Add(new SqlParameter("@OrderID", TheOrder.OrderID));
                cmd3.Parameters.Add(new SqlParameter("@ProductID", odb.ProductID));
                cmd3.Parameters.Add(new SqlParameter("@UnitPrice", odb.UnitPrice));
                cmd3.Parameters.Add(new SqlParameter("@Quantity", odb.Quantity));
                cmd3.Parameters.Add(new SqlParameter("@Discount", odb.Discount));
                cmd3.Transaction = Trans;
                cmd3.ExecuteNonQuery();
            }
            Trans.Commit(); // Commit the transaction
            CloseDB();
            foreach (OrderDetailsBase odb in TheOrder.ListOrderDetailsBase)
            {
                odb.OrderID = TheOrder.OrderID;
            }
            
        }

        public static void DeleteOrder(int OrderID)
        {


        }
        public static DataRow GetProduct(int ProductID)
        {
            try
            {
                DataRow dr;
                ProductsBase PB = new ProductsBase();
                DataTable dtProducts = new DataTable();
                string sql = $"Select * From Products Where ProductID = {ProductID.ToString()}";
                SqlDataAdapter da;
                OpenDB();
                da = new SqlDataAdapter(sql, con);
                da.FillSchema(dtProducts, SchemaType.Source);
                da.Fill(dtProducts);
                CloseDB();
                //should be one row
                if (dtProducts.Rows.Count == 0)
                {
                    dr = null;
                    throw new Exception($"Nwind.GetProduct: ProductID {ProductID} not found");
                }
                 dr = dtProducts.Rows[0];
                return dr;

            }
            catch(Exception)
            {
                DataRow dr = null;
                return  dr;
            }
            //PB.ProductID = ProductID;
            //PB.ProductName = (string)dr["ProductName"];
            //PB.SupplierID = dr["SupplierID"] as int?;
            //PB.CategoryID = dr["CategoryID"] as int?;
            //PB.UnitPrice = dr["UnitPrice"] as decimal?;
            //PB.QuantityPerUnit = dr["QuantityPerUnit"] as string;
            //PB.UnitsInStock = dr["UnitsInStock"] as short?;
            //PB.UnitsOnOrder = dr["UnitsOnOrder"] as short?;
            //PB.ReorderLevel = dr["ReorderLevel"] as short?;
            //PB.Discontinued = (bool)dr["Discontinued"];
            //return PB;


        }
    }
}
