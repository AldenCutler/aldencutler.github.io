import { useState } from "react";
import {
  Terminal,
  Code,
  Shield,
  Award,
  BookOpen,
  Briefcase,
  Download,
  Mail,
  Github,
  Linkedin,
  ExternalLink,
} from "lucide-react";

export default function Portfolio() {
  const [activeSection, setActiveSection] = useState("about");

  const sections = [
    { id: "about", label: "About", icon: Terminal },
    { id: "experience", label: "Experience", icon: Briefcase },
    { id: "skills", label: "Skills", icon: Code },
    { id: "projects", label: "Projects", icon: Shield },
    { id: "education", label: "Education", icon: BookOpen },
    { id: "awards", label: "Awards", icon: Award },
  ];

  const experience = [
    {
      title: "Software Engineer Intern",
      company: "Tesla",
      period: "May 2025 - August 2025",
      description: [
        "Developed firmware release management tools, reducing manual effort by 75% and CI/CD costs by 2.5x.",
        "Automated quantitative analysis of firmware releases using Jenkins, Python, and Splunk, saving 30 hours per quarter.",
        "Fixed misreporting metric affecting 400,000+ Tesla Energy devices through improved release tooling.",
        "Reduced firmware release sign-off checklist creation time by 80% with Jenkins automation.",
        "Enhanced security by configuring firewall rules for Megapack internal computer.",
      ],
    },
    {
      title: "Cybersecurity Intern",
      company: "Boeing",
      period: "March 2022 - June 2022",
      description: [
        "Developed resource monitoring software using shell scripting, Python, and statistical analysis.",
        "Calculated standard resource usage ranges for aircraft onboard computer processes.",
      ],
    },
  ];

  const skills = {
    Security: ["Network Security", "Cryptography", "Ghidra", "GDB & GEF", "Wireshark"],
    Programming: ["Python", "JavaScript/TypeScript", "C/C++", "x86/x64 Assembly", "Java"],
    Tools: ["Git", "Docker", "Jenkins", "Confluence", "JIRA", "Azure DevOps"],
    Databases: ["PostgreSQL", "PGVector", "MongoDB"],
    Web: ["React", "Node.js", "REST APIs", "Tailwind CSS"],
  };

  const projects = [
    {
      name: "Hospital Web Application - Brigham and Women's Hospital",
      description:
        "Led a 10-person team using Agile methodologies to build a cloud-based web application prototype. Implemented pathfinding, map editor, service request modules, and voice-activated UI. Deployed to AWS with Docker containerization.",
      links: [],
      tech: ["PostgreSQL", "Express", "React", "Node.js", "TypeScript", "PrismaORM", "AWS EC2", "Docker"],
    },
    {
      name: "Lyon Transit System Analysis - WPI IQP",
      description:
        "Research project analyzing Lyon's public transit system efficiency. Created interactive maps showing wheelchair-accessible stops and outage patterns across metro lines. Built data visualizations using Python to process collected transit data.",
      links: [
        {
          name: "GitHub Repository",
          href: "https://github.com/AldenCutler/LyonE24",
          icon: Github,
        },
        {
          name: "Project Website",
          href: "https://aldencutler.github.io/LyonE24/",
          icon: ExternalLink,
        },
        {
          name: "Published Paper",
          href: "https://digital.wpi.edu/concern/student_works/4x51hp32n?locale=en",
          icon: Download,
        }
      ],
      tech: ["Python", "SQLite3", "Pandas", "Matplotlib"],
    },
    {
      name: "Passive Operating System Fingerprinting",
      description:
        "Developed a Python-based tool to identify operating systems using passive network traffic analysis. " + 
        "Utilized p0f to identify operating systems and trained a random forest classifier for improved accuracy.",
      links: [
        {
          name: "GitHub Repository",
          href: "https://github.com/AldenCutler/CS513FinalProject",
          icon: Github,
        },
      ],
      tech: ["Python", "Pyshark", "p0f", "Scikit-learn"],
    },
    {
      name: "ChordStorm",
      description:
        "Music recommendation web app that suggests songs based on weather and listening history using GPT-4 and Spotify's API.",
      links: [
        {
          name: "GitHub Repository",
          href: "https://github.com/AldenCutler/ChordStorm",
          icon: Github,
        },
      ],
      tech: ["Python", "Flask", "MongoDB", "Spotify API", "OpenAI GPT"],
    },
  ];

  const education = [
    {
      degree: "Master of Science in Computer Science, Specialization in Cybersecurity",
      school: "Worcester Polytechnic Institute",
      gpa: "3.8/4.0",
      year: "May 2026",
    },
    {
      degree: "Bachelor of Science in Computer Science, Minor in Data Science",
      school: "Worcester Polytechnic Institute",
      gpa: "3.8/4.0",
      year: "May 2026",
    },
    {
      degree: "High School Diploma",
      school: "Seattle Academy of Arts and Sciences",
      gpa: "3.96/4.0",
      year: "June 2022",
    }
  ];

  const awards = {
    "WPI": [
      "Dean's List (Fall 2023 - Present)", 
      "Presidential Scholarship (4-year, $21,000 per year)", 
      "Winner - GoatHacks 2024"
    ],
    "Seattle Academy of Arts and Sciences": [
      "National 2nd Place - AFA Cyberpatriot Competition",
      "1st Place - FRC Rookie of the Year 2019-2020",
      "1st Place - Think Award at FTC World Championships 2018-2019",
      "2nd Place - Oregon State Fair FRC Event 2022"
    ]
  };

  return (
    <div className="min-h-screen bg-linear-to-br from-gray-900 via-blue-900 to-gray-900 text-gray-100">
      {/* Header */}
      <header className="border-b border-cyan-500/30 bg-gray-900/80 backdrop-blur-sm sticky top-0 z-50">
        <div className="max-w-6xl mx-auto px-6 py-4">
          <div className="flex items-center justify-between">
            <div className="flex items-center gap-2">
              <Shield className="text-cyan-400" size={28} />
              <span className="text-xl font-mono font-bold text-cyan-400">
                {"<AldenCutler />"}
              </span>
            </div>
            <nav className="hidden md:flex gap-6">
              {sections.map((section) => (
                <button
                  key={section.id}
                  onClick={() => {
                    setActiveSection(section.id)
                    // scroll to the section
                    document.getElementById(section.id)?.scrollIntoView({
                      behavior: 'smooth',
                    });
                  }}
                  className={`font-mono text-sm transition-colors ${
                    activeSection === section.id
                      ? "text-cyan-400"
                      : "text-gray-400 hover:text-cyan-300"
                  }`}
                >
                  {section.label}
                </button>
              ))}
            </nav>
          </div>
        </div>
      </header>

      {/* Hero Section */}
      <section className="py-20 px-6">
        <div className="max-w-6xl mx-auto">
          <div className="flex flex-col items-center text-center">
            <img src="profile2.jpg" alt="Profile" className="w-32 rounded-xl mb-6" />
            {/* <div className="w-32 h-32 bg-gradient-to-br from-cyan-500 to-blue-600 rounded-full mb-6 flex items-center justify-center">
              <Terminal size={64} className="text-white" />
            </div> */}
            <h1 className="text-5xl font-bold mb-4 bg-linear-to-r from-cyan-400 to-blue-500 bg-clip-text text-transparent">
              Alden Cutler
            </h1>
            <p className="text-2xl text-cyan-300 mb-4 font-mono">
              Software Engineer & Security Engineer
            </p>
            <p className="text-gray-400 max-w-2xl mb-8">
              Building reliable, secure software at the intersection of systems, security, and real-world engineering. Experienced in systems programming, cybersecurity analysis, and full-stack software development.
            </p>
            <div className="flex gap-4">
              <a
                href="mailto:aldencutler84@gmail.com"
                className="flex items-center gap-2 px-6 py-3 bg-cyan-500 hover:bg-cyan-600 rounded-lg transition-colors font-mono"
              >
                <Mail size={20} />
                Contact
              </a>
              <a
                href="/AldenCutler_Resume_2025.pdf"
                className="flex items-center gap-2 px-6 py-3 border border-cyan-500 hover:bg-cyan-500/10 rounded-lg transition-colors font-mono"
                target="_blank"
              >
                <Download size={20} />
                Resume
              </a>
            </div>
            <div className="flex gap-6 mt-6">
              <a
                href="https://github.com/AldenCutler"
                className="text-gray-400 hover:text-cyan-400 transition-colors"
                target="_blank"
              >
                <Github size={24} />
              </a>
              <a
                href="https://linkedin.com/in/aldencutler"
                className="text-gray-400 hover:text-cyan-400 transition-colors"
                target="_blank"
              >
                <Linkedin size={24} />
              </a>
            </div>
          </div>
        </div>
      </section>

      {/* Main Content */}
      <div className="max-w-6xl mx-auto px-6 pb-20">
        {/* About Section */}
        <section id="about" className="mb-16">
          <h2 className="text-3xl font-bold mb-6 flex items-center gap-3 text-cyan-400 font-mono">
            <Terminal size={32} />
            About Me
          </h2>
          <div className="bg-gray-800/50 border border-cyan-500/30 rounded-lg p-8 backdrop-blur-sm">
            <p className="text-gray-300 leading-relaxed mb-4">
              I'm Alden Cutler, a computer science student in a combined
              Bachelor's/Master's program with a focus on cybersecurity and a
              minor in data science. I have hands-on experience from internships
              and projects spanning cybersecurity, systems programming, and
              software development, including work with Boeing and research
              abroad in Lyon.
            </p>
            <p className="text-gray-300 leading-relaxed">
              I enjoy building practical, well-engineered
              systems—from low-level programming and security analysis to modern
              web applications—and I'm especially interested in roles that blend
              software, systems, and real-world impact.
            </p>
          </div>
        </section>

        {/* Experience Section */}
        <section id="experience" className="mb-16">
          <h2 className="text-3xl font-bold mb-6 flex items-center gap-3 text-cyan-400 font-mono">
            <Briefcase size={32} />
            Experience
          </h2>
          <div className="space-y-6">
            {experience.map((job, idx) => (
              <div
                key={idx}
                className="bg-gray-800/50 border border-cyan-500/30 rounded-lg p-6 backdrop-blur-sm"
              >
                <h3 className="text-xl font-bold text-cyan-300">{job.title}</h3>
                <p className="text-blue-400 font-mono mb-2">
                  {job.company} | {job.period}
                </p>
                {/* <p className="text-gray-300">{job.description}</p> */}
                <ul className="space-y-2">
                  {job.description.map((desc, i) => (
                    <li
                      key={i}
                      className="flex items-start gap-3 text-gray-300"
                    >
                      <span className="text-cyan-400 mt-1">▹</span>
                      <span>{desc}</span>
                    </li>
                  ))}
                </ul>
              </div>
            ))}
          </div>
        </section>

        {/* Skills Section */}
        <section id="skills" className="mb-16">
          <h2 className="text-3xl font-bold mb-6 flex items-center gap-3 text-cyan-400 font-mono">
            <Code size={32} />
            Skills
          </h2>
          <div className="grid md:grid-cols-2 gap-6">
            {Object.entries(skills).map(([category, items]) => (
              <div
                key={category}
                className="bg-gray-800/50 border border-cyan-500/30 rounded-lg p-6 backdrop-blur-sm"
              >
                <h3 className="text-xl font-bold text-cyan-300 mb-4">
                  {category}
                </h3>
                <div className="flex flex-wrap gap-2">
                  {items.map((skill, idx) => (
                    <span
                      key={idx}
                      className="px-3 py-1 bg-blue-600/30 border border-blue-500/50 rounded-full text-sm font-mono"
                    >
                      {skill}
                    </span>
                  ))}
                </div>
              </div>
            ))}
          </div>
        </section>

        {/* Projects Section */}
        <section id="projects" className="mb-16">
          <h2 className="text-3xl font-bold mb-6 flex items-center gap-3 text-cyan-400 font-mono">
            <Shield size={32} />
            Projects
          </h2>
          <div className="grid md:grid-cols-2 gap-6">
            {projects.map((project, idx) => (
              <div
                key={idx}
                className="bg-gray-800/50 border border-cyan-500/30 rounded-lg p-6 backdrop-blur-sm hover:border-cyan-400/50 transition-colors"
              >
                <h3 className="text-xl font-bold text-cyan-300 mb-3">
                  {project.name}
                </h3>
                <p className="text-gray-300 mb-4">{project.description}</p>
                <div className="flex flex-wrap gap-2">
                  {project.tech.map((tech, i) => (
                    <span
                      key={i}
                      className="px-2 py-1 bg-cyan-600/20 border border-cyan-500/50 rounded text-xs font-mono"
                    >
                      {tech}
                    </span>
                  ))}
                </div>
                <div className="flex flex-wrap gap-2 mt-6">
                  {project.links.map((link, i) => (
                    <a
                      key={i}
                      href={link.href}
                      target="_blank"
                      rel="noopener noreferrer"
                      className="flex items-center gap-1 px-2 py-1 bg-cyan-500/50 border border-cyan-600/20 rounded text-xs font-mono"
                    >
                      <link.icon size={18} />
                      {link.name}
                    </a>
                  ))}
                </div>
              </div>
            ))}
          </div>
        </section>

        {/* Education Section */}
        <section id="education" className="mb-16">
          <h2 className="text-3xl font-bold mb-6 flex items-center gap-3 text-cyan-400 font-mono">
            <BookOpen size={32} />
            Education
          </h2>
          <div className="space-y-4">
            {education.map((edu, idx) => (
              <div
                key={idx}
                className="bg-gray-800/50 border border-cyan-500/30 rounded-lg p-6 backdrop-blur-sm"
              >
                <h3 className="text-xl font-bold text-cyan-300">
                  {edu.degree}
                </h3>
                <p className="text-blue-400 font-mono">
                  {edu.school} | {edu.year} | GPA: {edu.gpa}
                </p>
              </div>
            ))}
          </div>
        </section>

        {/* Awards Section */}
        <section id="awards" className="mb-16">
          <h2 className="text-3xl font-bold mb-6 flex items-center gap-3 text-cyan-400 font-mono">
            <Award size={32} />
            Awards & Certifications
          </h2>
          <div className="space-y-4">
            {Object.entries(awards).map(([institution, awardsList]) => (
              <div className="bg-gray-800/50 border border-cyan-500/30 rounded-lg p-6 backdrop-blur-sm">
                <h3 className="text-xl font-bold text-cyan-300 mb-3">
                  {institution}
                </h3>
                <ul className="space-y-3">
                  {awardsList.map((award, i) => (
                    <li key={i} className="flex items-start gap-3 text-gray-300">
                      <span className="text-cyan-400 mt-1">▹</span>
                      <span>{award}</span>
                    </li>
                  ))}
                </ul>
              </div>
            ))}
            
          </div>
        </section>

        {/* Resume Download */}
        <section id="resume" className="text-center">
          <a
            href="/AldenCutler_Resume_2025.pdf"
            className="inline-flex items-center gap-3 px-8 py-4 bg-linear-to-r from-cyan-500 to-blue-600 hover:from-cyan-600 hover:to-blue-700 rounded-lg transition-all font-mono text-lg shadow-lg shadow-cyan-500/20"
            target="_blank"
          >
            <Download size={24} />
            Download Full Resume
          </a>
        </section>
      </div>

      {/* Footer */}
      <footer className="border-t border-cyan-500/30 bg-gray-900/80 backdrop-blur-sm py-8">
        <div className="max-w-6xl mx-auto px-6 text-center text-gray-400 font-mono">
          <p>© 2024 Your Name. Built with React & Tailwind CSS.</p>
        </div>
      </footer>
    </div>
  );
}
