using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ComputerController : MonoBehaviour {
    public Text healthIndicator;
    private int health;
    private Vector3 velocity;
    public float speed = 2.0f;
    public GameController gameController;
    private bool canFire;
    public GameObject bullet;
     private SpriteRenderer rend;


    // Start is called before the first frame update
    void Start()
    {
        rend = GetComponent<SpriteRenderer> ();
        canFire = true;
        health = 3;
        float xVel = Random.Range(-1, 1);
        while(xVel == 0)
            xVel = Random.Range(-1, 1);
        velocity = new Vector3(xVel,0, 0);
    }

    // Update is called once per frame
    void Update() {
        //1% of the time, switch the direction: 
        int change = Random.Range(0,100);
        if (change == 0)
        {
            velocity = new Vector3(-velocity.x, 0, 0);
        }

        var dist = (transform.position - Camera.main.transform.position).z;
        var leftBorder = Camera.main.ViewportToWorldPoint(new Vector3(0, 0, dist)).x;
        var rightBorder = Camera.main.ViewportToWorldPoint(new Vector3(1, 0, dist)).x;
        var bottomBorder = Camera.main.ViewportToWorldPoint(new Vector3(0, 0, dist)).y;
        var topBorder = Camera.main.ViewportToWorldPoint(new Vector3(0, 1, dist)).y;
        
        //get the width of the object
        float width = rend.bounds.size.x;
        float height = rend.bounds.size.y;
        if((transform.position.x <= leftBorder + width/2.0) && velocity.x < 0f){
            velocity = new Vector3(-velocity.x, 0f, 0f);
        }
        if((transform.position.x >= rightBorder - width/2.0) && velocity.x > 0f){
            velocity = new Vector3(-velocity.x, 0f, 0f);
        }
        if((transform.position.y <= bottomBorder + height/2.0) && velocity.y < 0f){
                velocity = new Vector3(0f, -velocity.y, 0f);
        }
        if((transform.position.y >= topBorder - height/2.0) && velocity.y > 0f){
            velocity = new Vector3(0f, -velocity.y, 0f);
        }
        transform.position = transform.position + velocity * Time.deltaTime * speed;

        if (canFire) {
            //the offset 
            Vector3 offset = new Vector3(0f, -2f, 0f);

           //creates a bullet that is pointing in the opposite direction... pick the one you need  
            GameObject b = Instantiate(bullet, new Vector3 (0f, 0f, 0f), Quaternion.AngleAxis(180, Vector2.left));


            b.GetComponent<BulletController>().InitPosition(transform.position + offset, new Vector3(0f, 2f, 0f));
            canFire = false;

            //this starts a coroutine... a non-blocking function
            StartCoroutine(PlayerCanFireAgain());

        }
    }

    IEnumerator PlayerCanFireAgain() {
        //this will pause the execution of this method for 3 seconds without blocking
        yield return new WaitForSecondsRealtime(3);
        canFire = true;
    }

    void OnTriggerEnter2D(Collider2D other) {
        healthIndicator.text += "X";
        health--;
        if(health == 0){
            gameController.gameOver(gameObject.name);
            Destroy(gameObject);   
        }    
    }
}
