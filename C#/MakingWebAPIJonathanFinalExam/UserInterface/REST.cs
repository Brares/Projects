using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net;
using System.IO;

namespace TestAPI
{
    public class RestParameter
    {
        public string Name;
        public string Value;

        public RestParameter(string name, string value)
        {
            this.Name = name;
            this.Value = value;
        }
        public string RESTFormat()
        {
            StringBuilder result = new StringBuilder();
            result.Append(Name);
            result.Append("=");
            result.Append(WebUtility.UrlEncode(Value));
            result.Append("&");
            return result.ToString();
        }
    }


    public class REST
    {
        public static string HttpGet(string url)
        {
            string result;
            HttpWebRequest req = WebRequest.Create(new Uri(url))
                                  as HttpWebRequest;
            req.Method = "GET";
            try
            {
                result = null;
                using (HttpWebResponse resp = req.GetResponse()
                                              as HttpWebResponse)

                {
                    using (StreamReader reader =
                        new StreamReader(resp.GetResponseStream()))
                    {
                        result = reader.ReadToEnd();
                        return result;
                    }
                }

            }
            catch (WebException wex)
            {

                using (var stream = wex.Response.GetResponseStream())
                using (var reader = new StreamReader(stream))
                {
                    result = reader.ReadToEnd();
                    throw new WebException("Server Error: " + wex.Message + "\n\r" + result);
                }
            }

        }

        public static string HttpGetWithParams(string url, List<RestParameter> RestParameters)
        {
            string Params = "";
            foreach (RestParameter rp in RestParameters)
            {
                Params += rp.RESTFormat();
            }
            url += "?" + Params;
            HttpWebRequest req = WebRequest.Create(new Uri(url))
                                 as HttpWebRequest;
            string result = null;
            using (HttpWebResponse resp = req.GetResponse()
                                          as HttpWebResponse)
            {
                StreamReader reader =
                    new StreamReader(resp.GetResponseStream());
                result = reader.ReadToEnd();
            }
            return result;
        }


        public static string HttpPostorPatch(string url, string[] paramName, string[] paramVal, string PostorPatch)
        {
            HttpWebRequest req = WebRequest.Create(new Uri(url))
                                 as HttpWebRequest;
            req.Method = PostorPatch;
            req.ContentType = "application/json";

            // Build a string with all the params, properly encoded.
            // We assume that the arrays paramName and paramVal are
            // of equal length:
            byte[] formData = null;
            if (paramName != null)
            {
                StringBuilder paramz = new StringBuilder();
                for (int i = 0; i < paramName.Length; i++)
                {
                    paramz.Append(paramName[i]);
                    paramz.Append("=");
                    paramz.Append(WebUtility.UrlEncode(paramVal[i])); //original had HttpUtility
                    paramz.Append("&");

                    // Encode the parameters as form data:
                    formData = UTF8Encoding.UTF8.GetBytes(paramz.ToString());
                    req.ContentLength = formData.Length;
                }
            }
            else
            {
                formData = new byte[0];
                req.ContentLength = 0;
            }

            // Send the request:
            using (Stream post = req.GetRequestStream())
            {
                post.Write(formData, 0, formData.Length);
            }

            // Pick up the response:
            try
            {
                string result = null;
                using (HttpWebResponse resp = req.GetResponse()
                                              as HttpWebResponse)
                {
                    StreamReader reader =
                        new StreamReader(resp.GetResponseStream());
                    result = reader.ReadToEnd();
                }
                return result;
            }

            catch (WebException wex)
            {

                using (var stream = wex.Response.GetResponseStream())
                using (var reader = new StreamReader(stream))
                {
                    string result = reader.ReadToEnd();
                    throw new WebException("Server Error: " + wex.Message + "\n\r" + result);
                }
            }


            catch (Exception)
            {

                throw;
            }


        }

        public static object HttpPostJSONObject(string url, String JSonObject)
        {
            //will rethrow a WebException with Server information in the message
            //Set up the REQUEST
            HttpWebRequest req = WebRequest.CreateHttp(url);
            req.Method = "POST";
            req.AllowWriteStreamBuffering = false;
            req.ContentType = "application/json";
            req.Accept = "Accept=application/json";
            req.SendChunked = false;
            req.ContentLength = JSonObject.Length;
            //Send the Request
            using (var sw = new StreamWriter(req.GetRequestStream()))
            {
                sw.Write(JSonObject);
            }

            // Pick up the response:
            string result = null;
            try
            {
                using (HttpWebResponse resp = req.GetResponse()
                                               as HttpWebResponse) //this throws an error if anything but 200 level message returned, but you can catch the error and read from the response stream - see below
                {
                    StreamReader reader =
                        new StreamReader(resp.GetResponseStream());
                    result = reader.ReadToEnd();
                }

                return result;

            }
            catch (WebException wex)
            {

                using (var stream = wex.Response.GetResponseStream())
                using (var reader = new StreamReader(stream))
                {
                    result = reader.ReadToEnd();
                    throw new WebException("Server Error: " + wex.Message + "\n\r" + result);
                }
            }






        }


    }



}
