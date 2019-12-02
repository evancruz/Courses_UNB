import java.util.*;
public class SearchBookUI {
	private SearchBookControl searchBookControl;
	
	public SearchBookUI(SearchBookControl control) {
		this.searchBookControl = control;
	}

	public void displaySearchForm() {
		System.out.println("Enter one or more keywords separated by space ' ' end by 0");
	}
	
	public void enterKeywords() {
		Scanner scanner = new Scanner(System.in);
		ArrayList<String> keywordList = new ArrayList<String>();
		while (true) {
			String keyword = scanner.next();
			if (keyword.equals("0")) break;
			keywordList.add(keyword);
		}
		scanner.close();
		
		ArrayList<BookInfoObject> books = searchBookControl.processSearchBook(keywordList);
		
		displayBooks(books);
	}
	
	public void displayBooks(ArrayList<BookInfoObject> books) {
		if (books.size() == 0) 
			System.out.println("No book is found.");
		else {
			System.out.println("Book Search Results: ");
			for(int i = 0; i < books.size(); i++) {
				System.out.println("Title: " + books.get(i).title);
				System.out.println("Author: " + books.get(i).author); 
				System.out.println("Description: " + books.get(i).description);
				System.out.println("Publisher: " + books.get(i).publisher);
				System.out.println("Year: " + books.get(i).year);
				System.out.println("ISBN: " + books.get(i).isbn); 
				System.out.println();
			}
		}
	}
}
