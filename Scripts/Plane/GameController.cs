using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;
public class GameController : MonoBehaviour {
    public GameObject obstacle;
    private ArrayList obstacles;
    public Text scoreText;
    public Text gameOverText;


    void Start () {
        obstacles = new ArrayList();
        CreateObstacles();
    }
    
    // Update is called once per frame
    void Update () {
        if(Input.GetKeyDown(KeyCode.R)){
            SceneManager.LoadScene(SceneManager.GetActiveScene().name);
        }
        if (Input.GetKey("escape")) {
            Application.Quit();
        }
        scoreText.text = "Obstacles remaining: "+ obstacles.Count;

        //to be completed
    }

    public void CreateObstacles(){
        //you should create at least 3 obstacles with different rotations 
        //and in different positions
        //note: we are adding them to the ArrayList created above

        //Instantiate can take the transform (position vector) 
        //and rotation quaternion as parameters

        obstacles.Add(
            Instantiate(obstacle, new Vector3(2,20,20), Quaternion.identity)
        );

        //Quaternion.AngleAxis creates a Quaternion object that is defined by 
        //the number of degrees of rotation around a provided axis. 
        //Below we provide the up axis (or y-axis)
        obstacles.Add(
            Instantiate(obstacle, new Vector3(20,45,65), Quaternion.AngleAxis(75f, Vector3.up))
        ); 

        obstacles.Add(
            Instantiate(obstacle, new Vector3(-5,30,-25), Quaternion.AngleAxis(15f, Vector3.up))
        ); 
    }

    //This method is to be called by the FlyingCraft when it successfully
    //makes it through a gap. The first parameter is the obstacle,
    //the second parameter is the FlyingCraft game object.
    public void Score(GameObject obstacle, GameObject sender) {
        //check if the obstacle is in the list
        //i.e., has not yet been passed through
        if (obstacles.Contains(obstacle)) {
            obstacles.Remove(obstacle);
        }

        if (obstacles.Count == 0) {
            Win();
            sender.SendMessage("Stop");
        }
    }

    public void GameOver(){
        gameOverText.text = "You lose \nPress R to restart";
    }
    
    private void Win() {
        gameOverText.text = "YOU WIN \nPress R to restart";
    }
}