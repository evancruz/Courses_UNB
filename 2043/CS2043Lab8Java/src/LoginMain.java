import java.util.Scanner;

public class LoginMain {
	public static void main(String[] args) {
		//private final CustomerObject customerObject;
		DataManager dm = new DataManager();
		Scanner scan = new Scanner(System.in);
		System.out.println("Enter Name");
		String name = scan.next();
		System.out.println("Enter Pass");
		String pass = scan.next();
		System.out.println("You entered: " + name + " " + pass);
		
		/*SearchBookControl control = new SearchBookControl(dm);
		SearchBookUI ui = new SearchBookUI(control);
		
		ui.displaySearchForm();
		ui.enterKeywords(); */
	};
	
	
}
