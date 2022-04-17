using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using MySql.Data.MySqlClient;

namespace Tutorial.SqlConn
{
    class DBUtils
    {
        public static MySqlConnection GetDBConnection()
        {
            string host = "localhost";
            int port = 3306;
            string database = "body_2.0";
            string username = "dimaib";
            string password = "23092309";
            return DBMySQLUtils.GetDBConnection(host, port, database, username, password);
        }

    }
}