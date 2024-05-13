const form = document.getElementById("form")
const msg = document.getElementById("msg")
const inp = document.getElementById("url") 

const messages = {
  "copied": "copied to clipboard",
  "submit": "hit enter to submit",
  "desc": "a simple link shortener",
}

inp.addEventListener("focusin", ()=>{
  msg.innerText = messages["submit"]
})

inp.addEventListener("focusout", ()=>{
  msg.innerText = messages["desc"]
})

form.addEventListener("submit", async(e)=>{
  e.preventDefault()
  const res = await fetch(`/add?url=${encodeURIComponent(inp.value)}`)
  const txt = await res.text()

  if(res.status != 200)
    return alert(txt)

  try {
    navigator.clipboard.writeText(txt)
  }catch(e) {
    return alert(txt)
  }

  msg.innerText = messages["copied"]
  inp.value = ""

  setTimeout(()=>{
    if(document.activeElement == inp)
      msg.innerText = messages["submit"]
    else
      msg.innerText = messages["desc"] 
  }, 1500)
})
