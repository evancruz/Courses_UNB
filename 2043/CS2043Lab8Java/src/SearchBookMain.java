public class SearchBookMain {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		DataManager dm = new DataManager();
		SearchBookControl control = new SearchBookControl(dm);
		SearchBookUI ui = new SearchBookUI(control);
		
		ui.displaySearchForm();
		ui.enterKeywords();
	};
}

