window.onload = function() {
    accessNotes();
    backToNoteHome();
    savingNotes();
    document.querySelector(".note_focus_window").style.display = "none";
    document.querySelector(".note_homepage").style.display = "flex";
};

function showNoteFocus()
{
    let noteWindow = document.querySelector(".note_focus_window");
    noteWindow.style.display = "flex";

    let mainWindow = document.querySelector(".note_homepage");
    mainWindow.style.display = "none";
    
}

function showNoteHome()
{
    let mainWindow = document.querySelector(".note_homepage");
    mainWindow.style.display = "flex";

    let noteWindow = document.querySelector(".note_focus_window");
    noteWindow.style.display = "none";
}

function accessNotes()
{
    x=document.getElementsByClassName("buttonNotes");
    for(var i = 0; i < x.length; i++)
    {
        x[i].innerText="Note " + (i+1);
        x[i].addEventListener("click", (event) => showNoteFocus());
    }
}

function backToNoteHome()
{
    backButton = document.getElementsByClassName("buttonheader")
    for(var i = 0; i < backButton.length; i++)
    {
        backButton[i].addEventListener("click", (event) => checkCurrentView());
    }
}

function checkCurrentView()
{
    let mainWindow = document.querySelector(".note_homepage");
    mainWindow.style.display = "flex";
    
    let noteWindow = document.querySelector(".note_focus_window");
    noteWindow.style.display = "none";
}

function savingNotes()
{
    saveButton = document.getElementsByClassName("save")
    saveButton[0].addEventListener("click", (event) => alert("Your note has been saved"));
}