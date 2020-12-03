using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BaseLayerObjects
{
    public class Customer
    {
        public static Customer GetCustomer(string CustomerID)
        {
            // will retrieve information from the DB and return a Customer object matching what it found in the DB

            throw new NotImplementedException();

        }
        public string CustomerID { get; set; }
        public string CompanyName { get; set; }
        public string ContactName { get; set; }
        public string ContactTitle { get; set; }
        public string Address { get; set; }
        public string City { get; set; }
        public string Region { get; set; }
        public string PostalCode { get; set; }
        public string Country { get; set; }
        public string Phone { get; set; }
        public string Fax { get; set; }

        public Customer()
        {  }
        public Customer(
         string CustomerID,
         string CompanyName,
         string ContactName,
         string ContactTitle,
         string Address,
         string City,
         string Region,
         string PostalCode,
         string Country,
         string Phone,
         string Fax)
        {
            this.CustomerID = CustomerID;
            this.CompanyName = CompanyName;
            this.ContactName = ContactName;
            this.ContactTitle = ContactTitle;
            this.Address = Address;
            this.City = City;
            this.Region = Region;
            this.PostalCode = PostalCode;
            this.Country = Country;
            this.Phone = Phone;
            this.Fax = Fax;
        }



        public List<Order> Orders
        {
            get
            {

                //return orders for this customer
                throw new NotImplementedException();
            }
        }

    }
}
