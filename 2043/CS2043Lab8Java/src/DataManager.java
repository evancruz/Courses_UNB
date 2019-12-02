import java.sql.*;
import java.util.*;
public class DataManager {
	Connection connection = null;
	
	public DataManager() {
		 try {
	         Class.forName("com.mysql.jdbc.Driver").newInstance();
	     } catch (Exception e) {
	      System.err.println(e.toString());
	     }
		String url = "jdbc:mysql://cs2043.cs.unb.ca:3306/mcruz";
		try {
		connection = DriverManager.getConnection(url, "mcruz", "G24KIDxZ");
		} catch (SQLException e) {
		System.err.println("Database connection error.");
		}
	}
	
	public ArrayList<BookInfoObject> getBooksByKeywords(ArrayList<String> keywords) {
		ArrayList<BookInfoObject> bookList = new ArrayList<BookInfoObject>();
		try {
			Statement st = connection.createStatement();
			
			//create query string
			String sqlQuery = "select * from BookInfo where ";
			for (int i=0; i<keywords.size(); i++) {
				if (i < keywords.size() - 1)
					sqlQuery = sqlQuery + "Title like '%" + keywords.get(i) + "%' or ";
				else sqlQuery = sqlQuery + "Title like '%" + keywords.get(i) + "%';";
			}
			
			//execute SQL query
			ResultSet rs = st.executeQuery(sqlQuery);
			
			//convert retrieved rows to BookInfoObject[]
			while (rs.next()) {
				BookInfoObject book = new BookInfoObject();
				book.id = rs.getString(1);
				book.title = rs.getString(2);
				book.description = rs.getString(3);
				book.author = rs.getString(4);
				book.isbn = rs.getString(5);
				book.publisher = rs.getString(6);
				book.year = rs.getInt(7);
				book.inventory = rs.getInt(8);
				bookList.add(book);
			}
		} catch (SQLException e) {
			System.err.println("SQL error: getBooksByKeywords");
		}
		
		return bookList;
	}
}

