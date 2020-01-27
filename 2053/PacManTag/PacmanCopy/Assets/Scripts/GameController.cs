using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;


public class GameController : MonoBehaviour {
    public Text gameOverText;
    public GameObject ghost;
    private float spawnTime;

    void Start() {
        Instantiate(ghost, new Vector3 (0f, 0f, 0f), Quaternion.identity);
        spawnTime = 0;
    }


    void Update() {
        
        spawnTime += Time.deltaTime;
        if(spawnTime > 5){
             Instantiate(ghost, new Vector3 (0f, 0f, 0f), Quaternion.identity);
             spawnTime = 0;
        }

        if(Input.GetKeyDown(KeyCode.R)){
            SceneManager.LoadScene(SceneManager.GetActiveScene().name);
        }
    }




    // Add a public GameOver method to your GameController, this method should set the state of your 
    // game to be completed 
    public void GameOver(){
        gameOverText.text = "GAME OVER \nPRESS R TO RESTART";
    }
}
