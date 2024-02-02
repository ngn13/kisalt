const inp = document.getElementById("url") 
const btn = document.getElementById("btn")
const form = document.getElementById("form")

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

  btn.innerText = "copied to clipboard"
  setTimeout(()=>{
    btn.innerText = "submit"
  }, 1500)
})
