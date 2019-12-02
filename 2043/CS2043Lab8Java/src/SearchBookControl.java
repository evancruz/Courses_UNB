import java.util.ArrayList;
public class SearchBookControl {
	private DataManager dataManager;
	
	public SearchBookControl(DataManager dm) {
		this.dataManager = dm;
	}
	
	public ArrayList<BookInfoObject> processSearchBook(ArrayList<String> keywords){
		return dataManager.getBooksByKeywords(keywords);
	}
}